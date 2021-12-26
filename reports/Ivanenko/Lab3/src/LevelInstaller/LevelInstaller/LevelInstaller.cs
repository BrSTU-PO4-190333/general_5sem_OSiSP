using System.IO;

namespace LevelInstaller
{
    public class LevelInstaller
    {
        private const string GameLevelsToInstallTo = "/home/tuesdaydude/src/labworks-5-semester/OS&SP/Lab1/Assets/Resources/levels.txt";
        
        private readonly Level _level;
        
        public LevelInstaller(Level level)
        {
            _level = level;
        }

        public void InstallLevel()
        {
            File.AppendAllText(GameLevelsToInstallTo, _level.LevelData);
        }
        
        
    }
}