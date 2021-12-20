using LevelInstaller;

namespace LevelUpdaterService.Services
{
    public class ClientService : IClientService
    {
        public void Update()
        {
            var levelInstaller = new Installer();
            levelInstaller.Update();
        }
    }
}