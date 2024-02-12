import React from 'react';
import { Input } from '@mui/base/Input';
import { styled } from '@mui/system';
import { ClassNames } from '@emotion/react';

const blue = {
  100: '#DAECFF',
  200: '#b6daff',
  400: '#3399FF',
  500: '#007FFF',
  600: '#0072E5',
  900: '#003A75',
};

const grey = {
  50: '#f6f8fa',
  100: '#eaeef2',
  200: '#d0d7de',
  300: '#afb8c1',
  400: '#8c959f',
  500: '#6e7781',
  600: '#57606a',
  700: '#424a53',
  800: '#32383f',
  900: '#24292f',
};

const StyledInputElement = styled('input')(
  ({ theme }) => `
  width: 20vw;
  height: 5vh;
  font-family: IBM Plex Sans, sans-serif;
  font-size: 0.875rem;
  font-weight: 400;
  line-height: 1.5;
  padding: 8px 12px;
  margin-top: 1vh;
  margin-bottom: 1vh; 
  border-radius: 8px;
  color: ${theme.palette.mode === 'dark' ? grey[300] : grey[900]};
  background: ${theme.palette.mode === 'dark' ? grey[900] : '#fff'};
  border: 2px solid ${theme.palette.mode === 'dark' ? grey[700] : grey[200]};
  box-shadow: 0px 2px 24px ${theme.palette.mode === 'dark' ? blue[900] : blue[100]};

  &:hover {
    border-color: ${blue[400]};
  }

  &:focus {
    border-color: ${blue[400]};
    box-shadow: 0 0 0 3px ${theme.palette.mode === 'dark' ? blue[600] : blue[200]};
  }

  &:focus-visible {
    outline: 0;
  }
`,
);

interface InputTakerProps {
  className: string;
  inputText: string;
  inputType: string;
  inputValue: string;
  inputValueFunction: (value: string) => void;
}

function InputTaker({className, inputText, inputType, inputValue, inputValueFunction }: InputTakerProps) {
    const handleInputChange = (event: React.ChangeEvent<HTMLInputElement>) => 
    {
      inputValueFunction(event.target.value);
    };
  
    return (
      <StyledInputElement
        className={className}
        aria-label="Demo input"
        placeholder={inputText}
        type={inputType}
        value={inputValue}
        onChange={handleInputChange}
      />
    );
  }

export default InputTaker;
