using WebServer;

namespace LevelUpdaterService.Services
{
    public class ServerService : IServerService
    {
        public void Up()
        {
            var server = new Server();
            server.Execute();
        }
    }
}