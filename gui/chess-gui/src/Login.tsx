import { useNavigate }  from 'react-router-dom';
import React from 'react';
import { tryCreatingConnectionSingletonInstance, getUserName } from './Connection.tsx'
import InputTaker from './inputTaker';
import { toast } from "./Toast/ToastManager";
import Button from '@mui/material/Button';
import { styled } from '@mui/system';
import './Login.css'



const GradientButton = styled(Button)`
  background-image: linear-gradient(to bottom, red, orange);
  border: 2px solid orange;
  color: white;
  font-weight: bold;
  padding: 12px 32px; /* Increase padding for bigger size */
  margin-top: 1vw;
  margin-left: 2vw;
  margin-right: 2vw;
  width: 8vw;
  font-size: 1.2rem; /* Increase font size for bigger text */

  &:hover {
    background-image: linear-gradient(to bottom, orange, yellow);
  }
`;

function Login() 
{    
    const [userName, setUserName] = React.useState<string>("");
    const [password, setPassword] = React.useState<string>("");
    const navigate = useNavigate();

    const signup = async () =>
    {        
        if(await tryCreatingConnectionSingletonInstance(userName, password, false))
        {
            navigate('/mainApp');
        }
        else
        {
            toast.show
            (
                {
                    title: "Error: Login",
                    content: "please try to login again",
                    duration: 5000,
                }
            )
        }
        
    }

    return(
        <div className="login-signup-div">
            <InputTaker
                className = "username-input"
                inputText="enter userName:"
                inputType="text"
                inputValue={userName}
                inputValueFunction={(value) => setUserName(value)}
            />

            <InputTaker
                className = "password-input"
                inputText="enter password:"
                inputType="password"
                inputValue={password}
                inputValueFunction={(value) => setPassword(value)}
            />

            <div className='signup-login-buttons'>
                <GradientButton
                    className = "signup-button"   
                    onClick={signup}
                >
                    signup</GradientButton>
                <GradientButton 
                    className = "login"
                    onClick={signup}>
                    login</GradientButton>
            </div>
        </div>
    );

}

export default Login;
