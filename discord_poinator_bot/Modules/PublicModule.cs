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
        private string answer = string.Empty;

        [Command("hello")]
        public async Task Hello(IUser user = null)
        {
            user = user ?? Context.User;
            answer += "Hello, <@" + user.Id.ToString() + ">";

            await ReplyAsync(answer);
        }

        [Command("about")]
        public async Task About()
        {
            answer += "Poinator bot\n";
            answer += "Ver 0.1.0 alpha\n";
            answer += "Created by LeakyRUS#9272\n";
            answer += "Project repository: https://github.com/leakyrus/poinator \n";
            answer += "3rd party:\n";
            answer += "\t\tzlib data compression library|| https://www.zlib.net/ ||\n";
            answer += "\t\tDiscord.Net|| https://github.com/discord-net/Discord.Net ||\n";
            answer += "\t\tMicrosoft Visual C++ Runtime library\n";
            answer += "\t\tMicrosoft .NET Framework";

            await ReplyAsync(answer);
        }

        [Command("help")]
        [Alias("?")]
        public async Task Help()
        {
            answer += "`help` - the list of commands that the bot can do\n";
            answer += "`hello` - ping you\n";
            answer += "`about` - brief\n";
            answer += "`encode` **message** - encoding your message to __Poi__ text. If __Poi__ text length bigger than 2k symbols then bot report an error\n";
            answer += "`decode` **message** - decoding your __Poi__ text to normal text\n";
            answer += "`roll` **[message]** - rolling between 1 and 20";

            await ReplyAsync(answer);
        }

        [Command("encode")]
        [RequireContext(ContextType.Guild)]
        public async Task Encode([Remainder] string text)
        {
            answer = FromDll.Encode(text);
            if (answer.Length > 1990) answer = "Encoded text length is bigger than 2k symbols";

            await ReplyAsync(answer);
        }

        [Command("decode")]
        public async Task Decode([Remainder] string text)
        {
            answer = FromDll.Decode(text);

            await ReplyAsync(answer);
        }

        [Command("roll")]
        public async Task Roll([Remainder] string text)
        {
            answer = "You roll ";
            Random rand = new Random((int)DateTime.Now.Ticks);
            answer += (rand.Next() % 20).ToString();
            answer += " " + text;

            await ReplyAsync(answer);
        }

        [Command("roll")]
        public async Task Roll()
        {
            answer = "You roll ";
            Random rand = new Random((int)DateTime.Now.Ticks);
            answer += ((rand.Next() % 21) - 1).ToString();

            await ReplyAsync(answer);
        }
    }
}