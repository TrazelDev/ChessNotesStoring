namespace chessBackendAPI
{
    public abstract class Singleton<T> where T : class, new()
    {
        private static T getInstance()
        {
            if(s_instance == null)
            {
                s_instance = new T();
            }

            return s_instance;
        }

        private static T s_instance;
    }
}
