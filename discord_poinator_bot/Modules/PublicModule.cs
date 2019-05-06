using System;
using System.Threading.Tasks;
using System.Collections;
using Discord;
using Discord.Commands;
using discord_poinator_bot.Services;
using System.Collections.Generic;
using static discord_poinator_bot.Static.ConstStrings.ApiSettings;

namespace discord_poinator_bot.Modules
{
    // Remember to make your module reference the ShardedCommandContext
    public class PublicModule : ModuleBase<ShardedCommandContext>
    {
        [Command("ping")]
        [Alias("!")]
        //[RequireBotPermission(ChannelPermission.ManageMessages, ErrorMessage = "Gimme a manage messages permission!")]
        public async Task Hello(IUser user = null)
        {
            string answer = string.Empty;
            var UserMessageId = Context.Message;

            try
            {
                await UserMessageId.DeleteAsync();
            }
            catch (Exception e) { }

            user = user ?? Context.User;
            answer += "*Pings* <@" + user.Id.ToString() + ">";

            await ReplyAsync(answer);

            GetLog.ToConsole(Context, "Hello");
        }

        [Command("about")]
        [Alias("/")]
        public async Task About()
        {
            string answer = string.Empty;
            answer += "I'm Poinator bot!\n";
            answer += "Ver 0.2.1 beta\n";
            answer += "Created by LeakyRUS#9272\n";
            answer += "Project repository: https://github.com/leakyrus/poinator \n";
            answer += "Don't look at .gitignore\n";
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

            embed.WithColor(255, 255, 255);

            await ReplyAsync(embed: embed.Build());

            GetLog.ToConsole(Context, "About");
        }

        [Command("help")]
        [Alias("?")]
        public async Task Help()
        {
            string answer = string.Empty;

            answer += "`help` (Alias: `?`) - the list of commands that the bot can do\n";
            answer += "`ping` **[user]** (Alias: `!`) - ping **you** or **[user]**\n";
            answer += "`about` (Alias: `/`) - brief\n";
            answer += "`encode` **<message>** (Alias: `>`) - encoding your **message** to __Poi__ text. Don't forget about 2k limit\n";
            answer += "`decode` **<message>** (Alias: `<`) - decoding your __Poi__ text to normal text\n";
            answer += "`roll` **[message]** (Alias: `%`) - rolling between 1 and 20 with **[message]**\n";
            answer += "`msg` **[message]** (Alias: `$`) - send a message on behalf of the bot";

            var embed = new EmbedBuilder
            {
                Title = "Bot commands! Use the `/` prefix",
                Description = answer
            };

            embed.WithColor(255, 255, 255);

            await ReplyAsync(embed: embed.Build());

            GetLog.ToConsole(Context, "Help");
        }

        [Command("encode")]
        [Alias(">")]
        //[RequireBotPermission(ChannelPermission.ManageMessages, ErrorMessage = "Gimme a manage messages permission!")]
        //[RequireContext(ContextType.Guild)]
        public async Task Encode([Remainder] string text = null)
        {
            string encoded = text != null ? FromDll.Encode(text) : null;
            IUser user = Context.User;
            var UserMessageId = Context.Message;

            try
            {
                await UserMessageId.DeleteAsync();
            }
            catch (Exception e) { }

            var embed = new EmbedBuilder();

            if (encoded != null)
            {
                if (encoded.Length > 1950)
                {
                    embed.WithTitle("Error!");
                    embed.WithDescription("Encoded text length is bigger than 2k symbols");
                    embed.WithColor(255, 128, 128);
                }
                else
                {
                    embed.WithTitle("Here is your encoded text!");
                    embed.WithAuthor(user);
                    embed.WithDescription($"```{encoded}```");
                    embed.WithColor(128, 255, 128);
                }
            }
            else
            {
                embed.WithTitle("Error!");
                embed.WithDescription("Your text is empty");
                embed.WithColor(255, 128, 128);
            }

            if (encoded != null)
            {
                if ((text.Length + encoded.Length) < 1950) embed.WithFooter($"Your text: {text}");
                else embed.WithFooter($"Your text is so big...");
            }

            await ReplyAsync(embed: embed.Build());

            GetLog.ToConsole(Context, "Encode");
        }

        [Command("decode")]
        [Alias("<")]
        //[RequireBotPermission(ChannelPermission.ManageMessages, ErrorMessage = "Gimme a manage messages permission!")]
        public async Task Decode([Remainder] string text = null)
        {
            string decoded = text != null ? FromDll.Decode(text) : null;
            IUser user = Context.User;
            var UserMessageId = Context.Message;

            try
            {
                await UserMessageId.DeleteAsync();
            }
            catch (Exception e) { }

            var embed = new EmbedBuilder();

            if (decoded != null)
            {
                embed.WithTitle("Here is your decoded text!");
                embed.WithAuthor(user);
                embed.WithDescription($"```{decoded}```");
                embed.WithColor(128, 255, 128);
            }
            else
            {
                embed.WithTitle("Error!");
                embed.WithDescription("Your text is empty");
                embed.WithColor(255, 128, 128);
            }

            await ReplyAsync(embed: embed.Build());

            GetLog.ToConsole(Context, "Decode");
        }

        [Command("roll")]
        [Alias("%")]
        //[RequireBotPermission(ChannelPermission.ManageMessages, ErrorMessage = "Gimme a manage messages permission!")]
        public async Task Roll([Remainder] string text = null)
        {
            IUser user = Context.User;
            int roll = new Random((int)DateTime.Now.Ticks).Next(1, 21);
            string rollMessage = string.Empty;
            var UserMessageId = Context.Message;

            try
            {
                await UserMessageId.DeleteAsync();
            }
            catch (Exception e) { }

            var embed = new EmbedBuilder();
            rollMessage += "You roll " + roll.ToString();
            embed.WithAuthor(user);
            embed.WithColor((int)((roll <= 10) ? ((21 - roll) * 12.8 - 1) : 127), (int)((roll > 10) ? (roll * 12.8 - 1) : 127), 127);

            if (text != null) embed.WithTitle(rollMessage + " " + text);
            else embed.WithTitle(rollMessage);

            await ReplyAsync(embed: embed.Build());

            GetLog.ToConsole(Context, "Roll");
        }

        [Command("msg")]
        [Alias("$")]
        //[RequireBotPermission(ChannelPermission.ManageMessages, ErrorMessage = "Gimme a manage messages permission!")]
        public async Task Message([Remainder] string text = null)
        {
            if(text != null)
            {
                await ReplyAsync(text);
            }

            try
            {
                await Context.Message.DeleteAsync();
            }
            catch (Exception e) { }

            GetLog.ToConsole(Context, "Message");
        }
    }
}