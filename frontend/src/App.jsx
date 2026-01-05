import React, { useState } from 'react';
import PixelButton from './components/PixelButton';
import PixelCard from './components/PixelCard';
import CodeEditor from './components/CodeEditor';
import AnalysisStats from './components/AnalysisStats';
import { Play } from 'lucide-react';
import './App.css';

function App() {
  const [code, setCode] = useState('public class Example {\n    public void test() {\n        if (true) {\n            System.out.println("Hello");\n        }\n    }\n}');
  const [stats, setStats] = useState(null);
  const [isAnalyzing, setIsAnalyzing] = useState(false);

  const analyzeCode = () => {
    setIsAnalyzing(true);

    // Simulate processing delay for effect
    setTimeout(() => {
      // Mock/Simple logic for demo
      const complexity = (code.match(/if|for|while|case|catch/g) || []).length + 1;

      // Rough nesting calculation (max open braces depth)
      let currentDepth = 0;
      let maxDepth = 0;
      for (const char of code) {
        if (char === '{') {
          currentDepth++;
          if (currentDepth > maxDepth) maxDepth = currentDepth;
        } else if (char === '}') {
          currentDepth--;
        }
      }

      // Random unused vars for demo flavor since static analysis is hard in JS regex
      const unusedVars = Math.floor(Math.random() * 3);

      setStats({
        complexity,
        nesting: maxDepth,
        unusedVars
      });
      setIsAnalyzing(false);
    }, 800);
  };

  return (
    <div className="app-container">
      <header className="header">
        <h1 className="title">8-BIT STATIC ANALYZER</h1>
        <div className="subtitle">JAVA CODE COMPLEXITY SCANNER</div>
      </header>

      <main style={{ display: 'grid', gridTemplateColumns: '1fr 350px', gap: '24px' }}>

        {/* Left Column: Editor */}
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

          {!stats && (
            <PixelCard>
              <div style={{ textAlign: 'center', color: '#888', padding: '20px' }}>
                <p>WAITING FOR INPUT...</p>
                <div style={{ fontSize: '3rem', marginTop: '10px' }}>👾</div>
              </div>
            </PixelCard>
          )}

          <PixelCard title="SYSTEM LOG">
            <div style={{ fontFamily: 'var(--code-font)', fontSize: '0.9rem', color: '#666', height: '150px', overflowY: 'auto' }}>
              <p>&gt; System initialized...</p>
              <p>&gt; Ready to scan.</p>
              {isAnalyzing && <p>&gt; Scanning code structure...</p>}
              {stats && <p>&gt; Analysis complete. <br />&gt; found {stats.complexity} complexity points.</p>}
            </div>
          </PixelCard>
        </div>

      </main>
    </div>
  );
}

export default App;
