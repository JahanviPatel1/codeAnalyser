const express = require('express');
const { exec } = require('child_process');
const fs = require('fs');
const path = require('path');
const db = require('../database');
const authenticateToken = require('../middleware/authMiddleware');

const router = express.Router();

router.post('/', authenticateToken, async (req, res) => {
    const { code } = req.body;
    const userId = req.user.id;

    if (!code) {
        return res.status(400).json({ error: 'No code provided' });
    }

    // 1. FIFO Eviction & Save (Transaction-like)
    // We'll do it in steps. SQLite serializes within a connection mostly.

    const processDatabase = new Promise((resolve, reject) => {
        db.serialize(() => {
            // Check count
            db.get('SELECT COUNT(*) as count FROM code_history WHERE user_id = ?', [userId], (err, row) => {
                if (err) return reject(err);

                if (row.count >= 5) {
                    // Delete oldest
                    db.run(`DELETE FROM code_history WHERE id = (
                        SELECT id FROM code_history WHERE user_id = ? ORDER BY id ASC LIMIT 1
                    )`, [userId]);
                }

                // Insert new
                db.run('INSERT INTO code_history (user_id, code_snippet) VALUES (?, ?)', [userId, code], function (err) {
                    if (err) return reject(err);
                    resolve(this.lastID);
                });
            });
        });
    });

    try {
        await processDatabase;

        // 2. Run Analyzer
        // Write code to temp file
        const tempFilePath = path.resolve(__dirname, '../../temp_submission.cpp');
        fs.writeFileSync(tempFilePath, code);

        // Execute binary
        // Assuming binary is at ../../bin/analyzer (relative to this file: backend/routes/analyze.js -> backend/routes -> backend -> Project2 -> bin)
        // Wait, __dirname is backend/routes.
        // ../../bin/analyzer is correct if backend is in root.
        const binaryPath = path.resolve(__dirname, '../../bin/analyzer');

        console.log(`Executing analyzer at: ${binaryPath} on file: ${tempFilePath}`);

        exec(`${binaryPath} ${tempFilePath}`, (error, stdout, stderr) => {
            // Clean up temp file
            try { fs.unlinkSync(tempFilePath); } catch (e) { }

            if (error) {
                console.warn(`Analyzer exited with code ${error.code}. Stdout length: ${stdout.length}. Stderr: ${stderr}`);

                // If we have output in stdout, it's likely a valid analysis of invalid code (e.g. syntax error report from analyzer)
                if (stdout && stdout.trim().length > 0) {
                    return res.json({ result: stdout });
                }

                // If no stdout, but stderr exists, return that as result 
                if (stderr) {
                    return res.status(200).json({ result: `Analysis Error:\n${stderr}` });
                }

                // Genuine failure
                return res.status(500).json({ error: 'Analyzer execution failed', details: error.message });
            }

            // Parse stdout assuming it's JSON from Phase 1? 
            // Phase 1 output might have been raw text or JSON. 
            // In the "Static Code Analyzer Project" output was expected to be analysis.
            // Let's assume we return the raw stdout for the frontend to parse or display.
            // Or if we need to return the history update as well?
            // The frontend can re-fetch history.

            res.json({ result: stdout });
        });

    } catch (err) {
        console.error('Database error:', err);
        res.status(500).json({ error: 'Database operation failed' });
    }
});

module.exports = router;
