import React from 'react';

const PixelButton = ({ children, onClick, variant = 'primary', className = '' }) => {
  const colors = {
    primary: 'var(--pixel-primary)',
    secondary: 'var(--pixel-secondary)',
    accent: 'var(--pixel-accent)',
  };

  const style = {
    backgroundColor: colors[variant] || colors.primary,
    border: '4px solid var(--pixel-border)',
    boxShadow: '4px 4px 0px 0px var(--pixel-border)',
    color: 'var(--pixel-fg)',
    padding: '12px 24px',
    fontSize: '1rem',
    textTransform: 'uppercase',
    outline: 'none',
    transition: 'all 0.1s',
    display: 'inline-flex',
    alignItems: 'center',
    justifyContent: 'center',
    gap: '8px',
  };

  return (
    <button
      className={className}
      style={style}
      onClick={onClick}
      onMouseDown={(e) => {
        e.currentTarget.style.transform = 'translate(2px, 2px)';
        e.currentTarget.style.boxShadow = '2px 2px 0px 0px var(--pixel-border)';
      }}
      onMouseUp={(e) => {
        e.currentTarget.style.transform = 'translate(0, 0)';
        e.currentTarget.style.boxShadow = '4px 4px 0px 0px var(--pixel-border)';
      }}
      onMouseLeave={(e) => {
        e.currentTarget.style.transform = 'translate(0, 0)';
        e.currentTarget.style.boxShadow = '4px 4px 0px 0px var(--pixel-border)';
      }}
    >
      {children}
    </button>
  );
};

export default PixelButton;
