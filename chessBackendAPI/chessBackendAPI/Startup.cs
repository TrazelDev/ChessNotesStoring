using ChessMessages;
using Spillman.SignalR.Protobuf;

namespace AspNetCoreSignalR_React.Server
{
    public class Startup
    {
        public void ConfigureServices(IServiceCollection services)
        {
            services.AddCors(o => o.AddPolicy("CorsPolicy", builder =>
            {
                builder
                    .AllowAnyMethod()
                    .AllowAnyHeader()
                    .AllowCredentials()
                    .WithOrigins("http://localhost:3000");
            }));

            

            services.AddSignalR()
                .AddMessagePackProtocol(options =>
                {

                });
        }

        public void Configure(IApplicationBuilder app, IWebHostEnvironment env)
        {
            app.UseRouting();
            app.UseCors("CorsPolicy");

            app.UseEndpoints(routes =>
            {
                routes.MapHub<LoginHub>("login");
            });
        }
    }
}
