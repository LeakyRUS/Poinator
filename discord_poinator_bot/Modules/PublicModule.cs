using System;
using System.Threading.Tasks;
using Discord;
using Discord.Commands;
using discord_poinator_bot.Services;

namespace discord_poinator_bot.Modules
{
    // Remember to make your module reference the ShardedCommandContext
    public class PublicModule : ModuleBase<ShardedCommandContext>
    {
        [Command("ping")]
        [Alias("!")]
        public async Task Hello(IUser user = null)
        {
            string answer = string.Empty;

            user = user ?? Context.User;
            answer += "Pong, <@" + user.Id.ToString() + ">";

            await ReplyAsync(answer);
        }

        [Command("about")]
        [Alias("/")]
        public async Task About()
        {
            string answer = string.Empty;
            answer += "I'm Poinator bot!\n";
            answer += "Ver 0.1.1 alpha\n";
            answer += "Created by LeakyRUS#9272\n";
            answer += "Project repository: https://github.com/leakyrus/poinator \n";
            answer += "3rd party:\n";
            answer += "- zlib data compression library https://www.zlib.net/ \n";
            answer += "- Discord.Net https://github.com/discord-net/Discord.Net \n";
            answer += "- Microsoft Visual C++ Runtime library\n";
            answer += "- Microsoft .NET Framework";

            var embed = new EmbedBuilder
            {
                Title = "Hello!",
                Description = answer,
                ImageUrl = Context.Client.CurrentUser.GetAvatarUrl()
            };
            
            await Context.Channel.SendMessageAsync("", embed: embed.Build());
        }

        [Command("help")]
        [Alias("?")]
        public async Task Help()
        {
            string answer = string.Empty;

            answer += "`help` (Alias: `?`) - the list of commands that the bot can do\n";
            answer += "`ping` (Alias: `!`) - ping you\n";
            answer += "`about` (Alias: `/`) - brief\n";
            answer += "`encode` **message** (Alias: `>`) - encoding your message to __Poi__ text. If __Poi__ text length bigger than 2k symbols then bot report an error\n";
            answer += "`decode` **message** (Alias: `<`) - decoding your __Poi__ text to normal text\n";
            answer += "`roll` **[message]** (Alias: `%`) - rolling between 1 and 20";

            var embed = new EmbedBuilder
            {
                Title = "Bot commands! Use the `/` prefix",
                Description = answer
            };

            await Context.Channel.SendMessageAsync("", embed: embed.Build());
        }

        [Command("encode")]
        [Alias(">")]
        [RequireContext(ContextType.Guild)]
        public async Task Encode([Remainder] string text)
        {
            string answer = string.Empty;
            string encoded = FromDll.Encode(text);
            IUser user = Context.User;

            var embed = new EmbedBuilder();

            if (encoded.Length > 1900)
            {
                embed.WithTitle("Error!");
                embed.WithDescription("Encoded text length is bigger than 2k symbols");
            }
            else
            {
                embed.WithTitle("Here is your encoded text!");
                embed.WithAuthor(user);
                embed.WithDescription($"```{encoded}```");
            }

            embed.WithFooter($"Your text: {text}");

            await Context.Channel.SendMessageAsync("", embed: embed.Build());
        }

        [Command("decode")]
        [Alias("<")]
        public async Task Decode([Remainder] string text)
        {
            string answer = string.Empty;
            string decoded = FromDll.Decode(text);
            IUser user = Context.User;

            var embed = new EmbedBuilder();

            embed.WithTitle("Here is your decoded text!");
            embed.WithAuthor(user);
            embed.WithDescription($"```{decoded}```");

            await Context.Channel.SendMessageAsync("", embed: embed.Build());
        }

        [Command("roll")]
        [Alias("%")]
        public async Task Roll([Remainder] string text = null)
        {
            IUser user = Context.User;

            var embed = new EmbedBuilder();
            embed.WithTitle("You roll " + new Random((int)DateTime.Now.Ticks).Next(1, 20).ToString());
            embed.WithAuthor(user);

            if (text != null) embed.WithDescription("Your message: " + text);

            await Context.Channel.SendMessageAsync("", embed: embed.Build());
        }
    }
}