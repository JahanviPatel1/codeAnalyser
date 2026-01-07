import { useState, useEffect } from 'react';
import PixelCard from './PixelCard';

const HistoryScroll = ({ onSelect, refreshTrigger, token }) => {
    const [history, setHistory] = useState([]);

    useEffect(() => {
        if (token) {
            fetch('http://localhost:3001/api/history', {
                headers: { 'Authorization': `Bearer ${token}` }
            })
                .then(res => res.json())
                .then(data => setHistory(data))
                .catch(err => console.error(err));
        }
    }, [token, refreshTrigger]);

    return (
        <PixelCard title="HISTORY SCROLL">
            <div style={{ display: 'flex', flexDirection: 'column', gap: '10px', height: '100%', maxHeight: '400px', overflowY: 'auto' }}>
                {history.length === 0 && <div style={{ color: '#888', textAlign: 'center' }}>NO DATA</div>}
                {history.map((item, index) => (
                    <div
                        key={item.id}
                        onClick={() => onSelect(item.code_snippet)}
                        style={{
                            padding: '10px',
                            border: '2px dashed #666',
                            cursor: 'pointer',
                            fontSize: '0.8rem',
                            fontFamily: 'monospace',
                            background: '#222',
                            color: '#d4d4d4'
                        }}
                    >
                        <div style={{ color: '#b19cd9' }}>ENTRY #{item.id}</div>
                        <div style={{ fontSize: '0.7rem', color: '#666' }}>{new Date(item.created_at).toLocaleString()}</div>
                    </div>
                ))}
            </div>
        </PixelCard>
    );
};

export default HistoryScroll;
