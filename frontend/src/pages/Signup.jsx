import { useState } from 'react';
import { useNavigate, Link } from 'react-router-dom';
import PixelCard from '../components/PixelCard';

const Signup = () => {
    const [username, setUsername] = useState('');
    const [password, setPassword] = useState('');
    const navigate = useNavigate();
    const [error, setError] = useState('');

    const handleSubmit = async (e) => {
        e.preventDefault();
        try {
            const response = await fetch('http://localhost:3001/api/auth/register', {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify({ username, password }),
            });
            const data = await response.json();
            if (response.ok) {
                navigate('/login');
            } else {
                setError(data.error);
            }
        } catch (err) {
            setError('Connection failed');
        }
    };

    return (
        <div style={{ display: 'flex', justifyContent: 'center', alignItems: 'center', height: '100vh', background: '#2d2d2d' }}>
            <PixelCard title="NEW CHARACTER">
                <form onSubmit={handleSubmit} style={{ display: 'flex', flexDirection: 'column', gap: '1rem', width: '300px' }}>
                    {error && <div style={{ color: '#ff6b6b', fontFamily: '"Press Start 2P", monospace', fontSize: '0.8rem' }}>! {error}</div>}

                    <div style={{ display: 'flex', flexDirection: 'column', gap: '5px' }}>
                        <label style={{ fontFamily: '"Press Start 2P", monospace', fontSize: '0.8rem', color: '#888' }}>CHOOSE NAME</label>
                        <input
                            type="text"
                            value={username}
                            onChange={(e) => setUsername(e.target.value)}
                            style={{ padding: '10px', fontFamily: '"Press Start 2P", monospace', border: '2px solid #4a4a4a', background: '#333', color: 'white', outline: 'none' }}
                        />
                    </div>

                    <div style={{ display: 'flex', flexDirection: 'column', gap: '5px' }}>
                        <label style={{ fontFamily: '"Press Start 2P", monospace', fontSize: '0.8rem', color: '#888' }}>SECRET CODE</label>
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
                            background: '#ffb3ba',
                            border: '4px solid #fff',
                            boxShadow: '4px 4px 0px #000',
                            fontFamily: '"Press Start 2P", monospace',
                            cursor: 'pointer',
                            color: '#2d2d2d'
                        }}
                    >
                        CREATE PLAYER
                    </button>

                    <div style={{ marginTop: '10px', textAlign: 'center', fontFamily: '"Press Start 2P", monospace', fontSize: '0.6rem', color: '#888' }}>
                        ALREADY JOINED? <Link to="/login" style={{ color: '#bae1ff' }}>LOGIN</Link>
                    </div>
                </form>
            </PixelCard>
        </div>
    );
};

export default Signup;
