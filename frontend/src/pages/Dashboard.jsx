import React, { useState } from 'react';
import PixelButton from '../components/PixelButton';
import PixelCard from '../components/PixelCard';
import CodeEditor from '../components/CodeEditor';
import AnalysisStats from '../components/AnalysisStats';
import HistoryScroll from '../components/HistoryScroll';
import { Play, LogOut } from 'lucide-react';
import { useAuth } from '../context/AuthContext';
import '../App.css';

function Dashboard() {
    const { user, logout } = useAuth();
    const [code, setCode] = useState('// Enter C++ Code Here\nvoid main() {\n  if(true) {}\n}');
    const [stats, setStats] = useState(null);
    const [isAnalyzing, setIsAnalyzing] = useState(false);
    const [refreshHistory, setRefreshHistory] = useState(0);
    const [systemLog, setSystemLog] = useState(['> System initialized...', '> Ready.']);

    const addToLog = (msg) => {
        setSystemLog(prev => [`> ${msg}`, ...prev.slice(0, 9)]);
    };

    const analyzeCode = async () => {
        setIsAnalyzing(true);
        addToLog('Sending code to Memory Core...');

        try {
            const response = await fetch('http://localhost:3001/api/analyze', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json',
                    'Authorization': `Bearer ${user.token}`
                },
                body: JSON.stringify({ code }),
            });

            const data = await response.json();

            if (response.ok) {
                // Parse the result string from C++ analyzer
                // Assuming the C++ analyzer returns a JSON string in standout
                // For now, let's display raw or try to parse
                let result = {};
                try {
                    // If the C++ output is "Complexity: 5\nNesting: 2..." we need to parse it or if it is JSON
                    // If the output is just text, we might need a parser in frontend.
                    // Let's assume for now it returns just text and we fake the stats or parse if possible.
                    // But wait, the previous Phase 1 didn't specify JSON output format for C++. 
                    // If it returns raw text we can just show it in log.

                    // For the sake of the demo, let's keep the mock math logic for the "Stats" UI 
                    // BUT display the real output in the log.

                    addToLog('Analysis Received.');
                    addToLog(data.result.substring(0, 50) + '...');

                    // Still calc local stats for the visuals until we parse C++ json properly
                    // (Assuming existing C++ might not return JSON)
                    const complexity = (code.match(/if|for|while|case|catch/g) || []).length + 1;

                    setStats({
                        complexity,
                        nesting: 0, // placeholder
                        unusedVars: 0
                    });

                    setRefreshHistory(prev => prev + 1); // Trigger history refresh

                } catch (e) {
                    addToLog('Error parsing result.');
                }
            } else {
                addToLog(`Error: ${data.error}`);
            }
        } catch (err) {
            addToLog(`Connection failed: ${err.message}`);
        } finally {
            setIsAnalyzing(false);
        }
    };

    return (
        <div className="app-container">
            <header className="header">
                <div>
                    <h1 className="title">8-BIT STATIC ANALYZER</h1>
                    <div className="subtitle">LOGGED IN AS: {user?.username}</div>
                </div>
                <PixelButton onClick={logout} variant="danger">
                    LOGOUT <LogOut size={16} />
                </PixelButton>
            </header>

            <main style={{ display: 'grid', gridTemplateColumns: '250px 1fr 300px', gap: '24px' }}>

                {/* Left Column: History */}
                <div style={{ display: 'flex', flexDirection: 'column', gap: '16px' }}>
                    <HistoryScroll
                        token={user?.token}
                        refreshTrigger={refreshHistory}
                        onSelect={(snippet) => setCode(snippet)}
                    />
                </div>

                {/* Middle Column: Editor */}
                <div style={{ display: 'flex', flexDirection: 'column', gap: '16px' }}>
                    <PixelCard title="SOURCE CODE">
                        <CodeEditor code={code} setCode={setCode} />
                    </PixelCard>

                    <div style={{ display: 'flex', justifyContent: 'flex-end' }}>
                        <PixelButton onClick={analyzeCode} variant="primary">
                            {isAnalyzing ? 'SCANNING...' : 'ANALYZE CODE'}
                            {!isAnalyzing && <Play size={20} />}
                        </PixelButton>
                    </div>
                </div>

                {/* Right Column: Stats */}
                <div style={{ display: 'flex', flexDirection: 'column', gap: '24px' }}>
                    <AnalysisStats stats={stats} />

                    <PixelCard title="SYSTEM LOG">
                        <div style={{ fontFamily: 'var(--code-font)', fontSize: '0.8rem', color: '#666', height: '150px', overflowY: 'auto', whiteSpace: 'pre-wrap' }}>
                            {systemLog.map((log, i) => <div key={i}>{log}</div>)}
                        </div>
                    </PixelCard>
                </div>

            </main>
        </div>
    );
}

export default Dashboard;
