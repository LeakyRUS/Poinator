using System;
using System.Threading.Tasks;
using discord_poinator_bot.Services;
using Discord;
using Discord.Commands;
using Discord.WebSocket;
using Microsoft.Extensions.DependencyInjection;

namespace discord_poinator_bot
{
    // This is a minimal example of using Discord.Net's Sharded Client
    // The provided DiscordShardedClient class simplifies having multiple
    // DiscordSocketClient instances (or shards) to serve a large number of guilds.
    class MainClass
    {
        static void Main(string[] args)
            => new MainClass().MainAsync().GetAwaiter().GetResult();

        public async Task MainAsync()
        {
            Modules.Utils.UptimeUtils.Begin();

            // You specify the amount of shards you'd like to have with the
            // DiscordSocketConfig. Generally, it's recommended to
            // have 1 shard per 1500-2000 guilds your bot is in.
            var config = new DiscordSocketConfig
            {
                TotalShards = 1
            };

            // You should dispose a service provider created using ASP.NET
            // when you are finished using it, at the end of your app's lifetime.
            // If you use another dependency injection framework, you should inspect
            // its documentation for the best way to do this.
            var services = ConfigureServices(config);
            var client = services.GetRequiredService<DiscordShardedClient>();

            // The Sharded Client does not have a Ready event.
            // The ShardReady event is used instead, allowing for individual
            // control per shard.
            client.ShardReady += ReadyAsync;
            client.Log += LogAsync;

            await services.GetRequiredService<CommandHandlingService>().InitializeAsync();

            // Tokens should be considered secret data, and never hard-coded.
            await client.LoginAsync(TokenType.Bot, Static.ConstStrings.ApiSettings.Token);
            await client.StartAsync();

            await Task.Delay(-1);
        }

        private IServiceProvider ConfigureServices(DiscordSocketConfig config)
        {
            return new ServiceCollection()
                .AddSingleton(new DiscordShardedClient(config))
                .AddSingleton<CommandService>()
                .AddSingleton<CommandHandlingService>()
                .BuildServiceProvider();
        }

        private Task ReadyAsync(DiscordSocketClient shard)
        {
            Console.WriteLine($"Shard Number {shard.ShardId} is connected and ready!");
            return Task.CompletedTask;
        }

        private Task LogAsync(LogMessage log)
        {
            Console.WriteLine(log.ToString());
            return Task.CompletedTask;
        }
    }
}