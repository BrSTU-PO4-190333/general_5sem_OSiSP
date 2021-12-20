using System;
using System.Threading;
using System.Threading.Tasks;
using LevelUpdaterService.Services;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;

namespace LevelUpdaterService
{
    public class Worker : BackgroundService
    {
        private readonly ILogger<Worker> _logger;
        private readonly IServiceScopeFactory _serviceScopeFactory;

        public Worker(ILogger<Worker> logger, IServiceScopeFactory serviceScopeFactory)
        {
            _logger = logger;
            _serviceScopeFactory = serviceScopeFactory;
        }

        protected override async Task ExecuteAsync(CancellationToken stoppingToken)
        {
            var scope = _serviceScopeFactory.CreateScope();
            var server = scope.ServiceProvider.GetService<IServerService>();
            var client = scope.ServiceProvider.GetService<IClientService>();
            while (!stoppingToken.IsCancellationRequested)
            {
                _logger.LogInformation("Worker running at: {time}", DateTimeOffset.Now);
                var serverThread = new Thread(server!.Up);
                serverThread.Start();
                Thread.Sleep(3000);
                var clientThread = new Thread(client!.Update);
                clientThread.Start();
                await Task.Delay(1000, stoppingToken);
            }
        }
    }
}
