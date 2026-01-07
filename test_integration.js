const axios = require('axios');

const API_URL = 'http://localhost:3001/api';

async function test() {
    try {
        const username = `testuser_${Date.now()}`;
        const password = 'password123';

        console.log('1. Registering User...');
        try {
            await axios.post(`${API_URL}/auth/register`, { username, password });
        } catch (e) {
            console.log('Registration might have failed if user exists:', e.message);
        }

        console.log('2. Logging in...');
        const loginRes = await axios.post(`${API_URL}/auth/login`, { username, password });
        const token = loginRes.data.token;
        const config = { headers: { Authorization: `Bearer ${token}` } };
        console.log('   Token received.');

        console.log('3. Submitting 6 snippets...');
        for (let i = 1; i <= 6; i++) {
            process.stdout.write(`   Submitting #${i}... `);
            await axios.post(`${API_URL}/analyze`, { code: `// Snippet ${i}` }, config);
            console.log('OK');
        }

        console.log('4. Checking History (FIFO)...');
        const historyRes = await axios.get(`${API_URL}/history`, config);
        const history = historyRes.data;

        console.log(`   Count: ${history.length} (Expected: 5)`);
        if (history.length !== 5) throw new Error('History count mismatch!');

        console.log('   Verifying Content...');
        // History is ordered by created_at DESC (Newest first)
        // So we expect Snippet 6, 5, 4, 3, 2. Snippet 1 should be gone.
        const invalid = history.find(h => h.code_snippet.includes('Snippet 1'));
        if (invalid) throw new Error('Snippet 1 found! FIFO failed.');

        const newest = history[0].code_snippet;
        if (!newest.includes('Snippet 6')) throw new Error('Newest snippet not found top of list.');

        console.log('✅ VERIFICATION PASSED: Gatekeeper & Memory Core operating within parameters.');

    } catch (err) {
        console.error('❌ TEST FAILED:', err.message);
        if (err.response) console.error('Data:', err.response.data);
    }
}

test();
