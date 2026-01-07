const express = require('express');
const db = require('../database');
const authenticateToken = require('../middleware/authMiddleware');

const router = express.Router();

// Get last 5 history items
router.get('/', authenticateToken, (req, res) => {
    const userId = req.user.id;
    const sql = `SELECT * FROM code_history WHERE user_id = ? ORDER BY id DESC LIMIT 5`;

    db.all(sql, [userId], (err, rows) => {
        if (err) return res.status(500).json({ error: err.message });
        res.json(rows);
    });
});

module.exports = router;
