import React from 'react';

const CodeEditor = ({ code, setCode }) => {
    return (
        <div style={{ width: '100%', height: '100%' }}>
            <label style={{
                display: 'block',
                marginBottom: '8px',
                fontSize: '0.8rem',
                color: '#666'
            }}>
        // INPUT SOURCE CODE BELOW:
            </label>
            <textarea
                value={code}
                onChange={(e) => setCode(e.target.value)}
                spellCheck="false"
                style={{
                    width: '100%',
                    minHeight: '300px',
                    padding: '16px',
                    backgroundColor: '#2d2d2d',
                    color: '#f8f8f2',
                    border: '4px solid var(--pixel-border)',
                    fontFamily: 'var(--code-font)',
                    fontSize: '1.2rem',
                    resize: 'vertical',
                    outline: 'none',
                    boxShadow: 'inset 4px 4px 0px 0px rgba(0,0,0,0.5)',
                }}
                placeholder="public class HelloWorld { ... }"
            />
        </div>
    );
};

export default CodeEditor;
