import { HubConnectionBuilder } from '@microsoft/signalr';
import * as msgpack from '@microsoft/signalr-protocol-msgpack'; // Import msgpack
import { SingupMsg } from './msgFormat'


class ConnectionSingleton {
  private static instance: ConnectionSingleton | null = null;
  private static userName: string | null = null;

  state: {
    hubConnection: any;
  };

  private constructor() {
    this.state = {
      hubConnection: null,
    };
  }

  private async setupHubConnection() {
    const hubConnection = new HubConnectionBuilder()
      .withUrl('http://localhost:5162/login')
      .withHubProtocol(new msgpack.MessagePackHubProtocol())
      .build();
      
      this.state.hubConnection = hubConnection;
      
      this.state.hubConnection.onclose(async () => {
        await this.setupHubConnection(); // Reconnect if the connection is closed
      });
      
      console.log("hello");
      await this.state.hubConnection.start();
      
      this.state.hubConnection.on('getData', this.getData);
  }

  private getData = (msg: Uint8Array) => {
    console.log("the information is:", msg);
  };


  private async signup(userName: string, password: string): Promise<boolean> {
    const signupMessage : SingupMsg = {name: userName, password : password};

    return await this.state.hubConnection.invoke('signup', SingupMsg.encode(signupMessage).finish()); 
  }

  private async login(username : string, password: string) : Promise<boolean>
  {
    const signupMessage : SingupMsg = {name: username, password : password};

    return await this.state.hubConnection.invoke('login', SingupMsg.encode(signupMessage).finish());
  }

  private async initializeConnection(): Promise<void> {
    await this.setupHubConnection();
  }

  public static async createInstance(newUserName: string, newPassword: string, loginOrNot: boolean): Promise<boolean> {    
    if (!ConnectionSingleton.instance) {
      ConnectionSingleton.instance = new ConnectionSingleton();
      await ConnectionSingleton.instance.initializeConnection();
    }
    
    const loginOrSignup = loginOrNot ? 
      await ConnectionSingleton.instance.login(newUserName, newPassword) : await ConnectionSingleton.instance.signup(newUserName, newPassword);
    
    if (loginOrSignup)
    {
      ConnectionSingleton.userName = newUserName;
      return true;
    }
    
    return false;
  }

  public static getInstance(): ConnectionSingleton {
    if (ConnectionSingleton.instance && ConnectionSingleton.userName) {
      return ConnectionSingleton.instance;
    }
    throw new Error("ConnectionSingleton instance has not been initialized.");
  }

  public static getUserName(): string {
    return ConnectionSingleton.userName as string;
  }
}

export const tryCreatingConnectionSingletonInstance = ConnectionSingleton.createInstance;
export const getUserName = ConnectionSingleton.getUserName;
