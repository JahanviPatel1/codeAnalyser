import { useState } from 'react';
import { useAuth } from '../context/AuthContext';
import { useNavigate, Link } from 'react-router-dom';
import PixelCard from '../components/PixelCard';

const Login = () => {
    const [username, setUsername] = useState('');
    const [password, setPassword] = useState('');
    const { login } = useAuth();
    const navigate = useNavigate();
    const [error, setError] = useState('');

    const handleSubmit = async (e) => {
        e.preventDefault();
        try {
            const response = await fetch('http://localhost:3001/api/auth/login', {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify({ username, password }),
            });
            const data = await response.json();
            if (response.ok) {
                login(data.token, data.username);
                navigate('/');
            } else {
                setError(data.error);
            }
        } catch (err) {
            setError('Connection failed');
        }
    };

    return (
        <div style={{ display: 'flex', justifyContent: 'center', alignItems: 'center', height: '100vh', background: '#2d2d2d' }}>
            <PixelCard title="PLAYER LOGIN">
                <form onSubmit={handleSubmit} style={{ display: 'flex', flexDirection: 'column', gap: '1rem', width: '300px' }}>
                    {error && <div style={{ color: '#ff6b6b', fontFamily: '"Press Start 2P", monospace', fontSize: '0.8rem' }}>! {error}</div>}

                    <div style={{ display: 'flex', flexDirection: 'column', gap: '5px' }}>
                        <label style={{ fontFamily: '"Press Start 2P", monospace', fontSize: '0.8rem', color: '#888' }}>USERNAME</label>
                        <input
                            type="text"
                            value={username}
                            onChange={(e) => setUsername(e.target.value)}
                            style={{ padding: '10px', fontFamily: '"Press Start 2P", monospace', border: '2px solid #4a4a4a', background: '#333', color: 'white', outline: 'none' }}
                        />
                    </div>

                    <div style={{ display: 'flex', flexDirection: 'column', gap: '5px' }}>
                        <label style={{ fontFamily: '"Press Start 2P", monospace', fontSize: '0.8rem', color: '#888' }}>PASSWORD</label>
                        <input
                            type="password"
                            value={password}
                            onChange={(e) => setPassword(e.target.value)}
                            style={{ padding: '10px', fontFamily: '"Press Start 2P", monospace', border: '2px solid #4a4a4a', background: '#333', color: 'white', outline: 'none' }}
                        />
                    </div>

                    <button
                        type="submit"
                        style={{
                            marginTop: '10px',
                            padding: '12px',
                            background: '#b19cd9',
                            border: '4px solid #fff',
                            boxShadow: '4px 4px 0px #000',
                            fontFamily: '"Press Start 2P", monospace',
                            cursor: 'pointer',
                            color: '#2d2d2d'
                        }}
                    >
                        START GAME
                    </button>

                    <div style={{ marginTop: '10px', textAlign: 'center', fontFamily: '"Press Start 2P", monospace', fontSize: '0.6rem', color: '#888' }}>
                        NEW PLAYER? <Link to="/signup" style={{ color: '#98ff98' }}>INSERT COIN</Link>
                    </div>
                </form>
            </PixelCard>
        </div>
    );
};

export default Login;
