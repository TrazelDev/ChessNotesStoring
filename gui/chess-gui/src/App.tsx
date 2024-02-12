import { Routes, Route } from 'react-router-dom';
import './App.css';
import Login from './Login.tsx';
import TopBar from './TopBar.tsx'
import PieChart from './PieChart.tsx'


function App() {
  return (
    <div className="chess-app">
      <Routes>
        <Route path="/" element={<Login></Login>} />
        <Route path="mainApp/*" element={<TopBar/>} />
        <Route path="*" element={<div>hello</div>} />
      </Routes>
      
    </div>
  );
}

export default App;
