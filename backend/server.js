const express = require('express');
const cors = require('cors');
const authRoutes = require('./routes/auth');
require('dotenv').config();

const app = express();
const PORT = process.env.PORT || 5000;

app.use(cors());
app.use(express.json());

// Routes
app.use('/api/auth', authRoutes);
app.use('/api/history', require('./routes/history'));
app.use('/api/analyze', require('./routes/analyze'));

app.get('/', (req, res) => {
    res.send('Antigravity API is running 🚀');
});

app.listen(PORT, () => {
    console.log(`Server is running on port ${PORT}`);
});
