import React from 'react';

const PixelCard = ({ children, title, className = '' }) => {
    const style = {
        backgroundColor: 'white',
        border: '4px solid var(--pixel-border)',
        boxShadow: 'var(--pixel-shadow)',
        padding: '24px',
        position: 'relative',
    };

    return (
        <div className={className} style={style}>
            {title && (
                <div style={{
                    position: 'absolute',
                    top: '-16px',
                    left: '16px',
                    background: 'var(--pixel-secondary)',
                    border: '4px solid var(--pixel-border)',
                    padding: '4px 12px',
                    fontSize: '0.8rem',
                    fontWeight: 'bold',
                }}>
                    {title}
                </div>
            )}
            {children}
        </div>
    );
};

export default PixelCard;
