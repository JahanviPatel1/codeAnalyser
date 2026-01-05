import React from 'react';
import PixelCard from './PixelCard';
import { Activity, GitBranch, Trash2 } from 'lucide-react';

const StatItem = ({ label, value, icon: Icon, color }) => (
    <div style={{ display: 'flex', alignItems: 'center', gap: '16px', marginBottom: '16px' }}>
        <div style={{
            background: color,
            padding: '8px',
            border: '2px solid var(--pixel-border)',
            display: 'flex',
            alignItems: 'center',
            justifyContent: 'center'
        }}>
            <Icon size={24} color="var(--pixel-fg)" />
        </div>
        <div>
            <div style={{ fontSize: '0.7rem', color: '#666', marginBottom: '4px' }}>{label}</div>
            <div style={{ fontSize: '1.5rem', color: 'var(--pixel-primary)' }}>{value}</div>
        </div>
    </div>
);

const AnalysisStats = ({ stats }) => {
    if (!stats) return null;

    return (
        <PixelCard title="ANALYSIS REPORT">
            <div style={{ display: 'grid', gap: '16px' }}>
                <StatItem
                    label="CYCLOMATIC COMPLEXITY"
                    value={stats.complexity}
                    icon={Activity}
                    color="var(--pixel-accent)"
                />
                <StatItem
                    label="MAX NESTING DEPTH"
                    value={stats.nesting}
                    icon={GitBranch}
                    color="var(--pixel-secondary)"
                />
                <StatItem
                    label="UNUSED VARIABLES"
                    value={stats.unusedVars}
                    icon={Trash2}
                    color="#ffcccb"
                />
            </div>

            {stats.complexity > 10 && (
                <div style={{
                    marginTop: '24px',
                    padding: '12px',
                    background: 'var(--pixel-primary)',
                    border: '2px solid var(--pixel-border)',
                    color: 'white',
                    textAlign: 'center',
                    animation: 'blink 1s infinite'
                }}>
                    !! WARNING: HIGH COMPLEXITY !!
                </div>
            )}
            <style>{`
        @keyframes blink {
          50% { opacity: 0.5; }
        }
      `}</style>
        </PixelCard>
    );
};

export default AnalysisStats;
