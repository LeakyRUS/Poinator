using System.IO;
using System.Threading.Tasks;
using Discord;
using Discord.Commands;

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
            answer += "Ver 0.0.2 alpha\n";
            answer += "Created by LeakyRUS#9272";

            await ReplyAsync(answer);
        }

        [Command("help")]
        [Alias("?")]
        public async Task Help()
        {
            answer += "`help` - list commands what bot can do\n";
            answer += "`hello` - ping you\n";
            answer += "`about` - information about bot\n";
            answer += "`encode` **message** - encoding your message to __Poi__ text. If __Poi__ text length bigger than 2k symbols then bot report an error\n";
            answer += "`decode` **message** - decoding your __Poi__ text to normal text";

            await ReplyAsync(answer);
        }

        [Command("encode")]
        [RequireContext(ContextType.Guild)]
        public async Task Encode([Remainder] string text)
        {
            answer += "On development!\n";
            answer += "Your message: " + text;

            await ReplyAsync(answer);
        }

        [Command("decode")]
        public async Task Decode([Remainder] string text)
        {
            answer += "On development!\n";
            answer += "Your message: " + text;

            await ReplyAsync(answer);
        }
    }
}