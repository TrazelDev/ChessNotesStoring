import React from 'react';
import AppBar from '@mui/material/AppBar';
import Box from '@mui/material/Box';
import Toolbar from '@mui/material/Toolbar';
import IconButton from '@mui/material/IconButton';
import Typography from '@mui/material/Typography';
import Menu from '@mui/material/Menu';
import MenuIcon from '@mui/icons-material/Menu';
import Container from '@mui/material/Container';
import Avatar from '@mui/material/Avatar';
import Button from '@mui/material/Button';
import Tooltip from '@mui/material/Tooltip';
import AdbIcon from '@mui/icons-material/Adb';
import ChessBoard from './Chessboard.tsx';
import { useNavigate, Routes, Route, Link }  from 'react-router-dom';
import PieChart from './PieChart.tsx'
import './TopBar.css'
import { useState } from 'react';

const pages = ['play', 'watch', ];


function ResponsiveAppBar() {
  const [activeButton, setActiveButton] = React.useState<null | string>(null);
  const navigate = useNavigate();
  const [ thisData, setData ] = useState<Notes[]>
    (
      [
        {
          name: 'Page A',
          notes: 10000,
          amt: 2400,
        },
        {
          name: 'Page B',
          notes: 4300,
          amt: 2210,
        },
        {
          name: 'Page C',
          notes: 4300,
          amt: 2290,
        },
        {
          name: 'Page D',
          notes: 4300,
          amt: 2000,
        },
        {
          name: 'Page E',
          notes: 4300,
          amt: 2181,
        },
        {
          name: 'Page F',
          notes: 4300,
          amt: 2500,
        },
        {
          name: 'Page G',
          notes: 4300,
          amt: 2100,
        },
      ]
    );

  const handleButtonClick = (page : string) => {
    setActiveButton(page);
    navigate('/mainApp/' + page);
  }

  const func = () => 
  {
    setData([
      {
        name: 'Page A',
        notes: 4300,
        amt: 2400,
      },
      {
        name: 'Page B',
        notes: 4300,
        amt: 2210,
      },
      {
        name: 'Page C',
        notes: 4300,
        amt: 2290,
      },
      {
        name: 'Page D',
        notes: 4300,
        amt: 2000,
      },
      {
        name: 'Page E',
        notes: 4300,
        amt: 2181,
      },
      {
        name: 'Page F',
        notes: 4300,
        amt: 2500,
      },
      {
        name: 'Page G',
        notes: 4300,
        amt: 2100,
      },
    ])
  }
  
  return (
    <div className="top-bar">
      <div className="app-bar">
        <AppBar
            className="app-bar"
            position="static"
            sx={{
                background: 'linear-gradient(to bottom, red, orange)',
                borderBottom: '2px solid orange',
            }}
            >
            <Container maxWidth="xl">
                <Toolbar disableGutters>
                <Typography
                    variant="h4"
                    noWrap
                    component="a"
                    sx={{
                    mr: 2,
                    display: { xs: 'none', md: 'flex' },
                    fontFamily: 'monospace',
                    fontWeight: 700,
                    letterSpacing: '.3rem',
                    color: 'inherit',
                    textDecoration: 'none',
                    }}
                >
                    Chess App
                </Typography>

                <AdbIcon sx={{ display: { xs: 'flex', md: 'none' }, mr: 1 }} />
                <Typography
                    variant="h6"
                    noWrap
                    component="a"
                    href="#app-bar-with-responsive-menu"
                    sx={{
                    mr: 2,
                    display: { xs: 'flex', md: 'none' },
                    flexGrow: 1,
                    fontFamily: 'monospace',
                    fontWeight: 700,
                    letterSpacing: '.3rem',
                    color: 'inherit',
                    textDecoration: 'none',
                    }}
                >
                    LOGO
                </Typography>
                <Box sx={{ flexGrow: 1, display: { xs: 'none', md: 'flex' } }}>
                    {pages.map((page) => (
                    <Button
                        key={page}
                        onClick={() => {
                            handleButtonClick(page); 
                        }}
                        sx={{
                            my: 2,
                            color: 'white',
                            display: 'block',
                            fontWeight: 'bold',
                            fontSize: '1.2rem',
                            padding: '8px 24px',
                            border: '2px solid transparent',
                            borderBottom: activeButton === page ? '2px solid white' : '2px solid transparent',
                        }}
                        >
                        {page}
                        </Button>
                    ))}
                </Box>
            </Toolbar>
            </Container>
        </AppBar>
      </div>

      <div className="routes">
        <Routes>
          <Route path="play" element={<ChessBoard />} />
          <Route path="watch" element={<div>hello my world</div>} />
        </Routes>
      </div>
                    
      
      <button className='temp' onClick={func}>temp</button>
      <div className="pie-chart">
        
        <PieChart data ={thisData}></PieChart>
      </div>
    </div>
  );
}
export default ResponsiveAppBar;