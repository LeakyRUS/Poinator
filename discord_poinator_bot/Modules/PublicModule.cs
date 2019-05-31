using System;
using System.Threading.Tasks;
using System.Collections;
using Discord;
using Discord.Commands;
using discord_poinator_bot.Services;
using System.Collections.Generic;
using static discord_poinator_bot.Static.ConstStrings.ApiSettings;
using Discord.WebSocket;

namespace discord_poinator_bot.Modules
{
    class MentC
    {
        public ulong count;
        public string name;
        public ulong online;
        public void CountInc()
        {
            count++;
        }

        public void OnlineInc()
        {
            online++;
        }
    }

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

            answer += "`help` (Alias: `?`) - the list of commands that the bot can do;\n";
            answer += "`ping` **[user]** (Alias: `!`) - ping **you** or **[user]**;\n";
            answer += "`about` (Alias: `/`) - brief;\n";
            answer += "`encode` **<message>** (Alias: `>`) - encoding your **message** to __Poi__ text. Don't forget about 2k limit;\n";
            answer += "`decode` **<message>** (Alias: `<`) - decoding your __Poi__ text to normal text;\n";
            answer += "`roll` **[message]** (Alias: `%`) - rolling between 1 and 20 with **[message]**;\n";
            answer += "`msg` **[message]** (Alias: `$`) - send a message on behalf of the bot;\n";
            answer += "`checkroles` **[-s]** **[-u]** **[\"role\"]** - make a list of roles, count and online. **-s** add **@** at the beginning of the role. **-u** means that the command contains the names of specific roles that need to be displayed.";

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
            string encoded = null;
            bool isError = false;

            try
            {
                encoded = text != null ? FromDll.Encode(text) : null;
            }
            catch (Exception e)
            {
                isError = true;
                encoded = e.Message;
            }

            IUser user = Context.User;
            var UserMessageId = Context.Message;

            try
            {
                await UserMessageId.DeleteAsync();
            }
            catch (Exception e) { }

            var embed = new EmbedBuilder();

            if (isError)
            {
                embed.WithTitle("Error!");
                embed.WithDescription(encoded);
                embed.WithColor(255, 128, 128);
            }
            else
            {
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
            }

            embed.WithAuthor(user);

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
            string decoded;
            bool isError = false;
            try
            {
                decoded = text != null ? FromDll.Decode(text) : null;
            }
            catch (Exception e)
            {
                isError = true;
                decoded = e.Message;
            }

            IUser user = Context.User;
            var UserMessageId = Context.Message;

            try
            {
                await UserMessageId.DeleteAsync();
            }
            catch (Exception e) { }

            var embed = new EmbedBuilder();

            if (isError)
            {
                embed.WithTitle("Error!");
                embed.WithDescription(decoded);
                embed.WithColor(255, 128, 128);
            }
            else
            {
                if (decoded != null)
                {
                    embed.WithTitle("Here is your decoded text!");
                    embed.WithDescription(decoded);
                    embed.WithColor(128, 255, 128);
                }
                else
                {
                    embed.WithTitle("Error!");
                    embed.WithDescription("Your text is empty");
                    embed.WithColor(255, 128, 128);
                }
            }

            embed.WithAuthor(user);

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

        [Command("checkroles")]
        //[Alias("$")]
        //[RequireBotPermission(ChannelPermission.ManageMessages, ErrorMessage = "Gimme a manage messages permission!")]
        public async Task CheckRoles(params string[] parameters)
        {
            var users = new List<IGuildUser>(Context.Guild.Users);
            var roles = new List<SocketRole>(Context.Guild.Roles);

            var pas = new List<string>(parameters);

            var mentionsCount = new List<MentC>();

            foreach (var user in users)
            {
                var userRolesIds = new List<ulong>(user.RoleIds);
                bool isOffline = user.Status == UserStatus.Offline;

                foreach(var role in roles)
                {
                    if (userRolesIds.Contains(role.Id))
                    {
                        try
                        {
                            var ex = mentionsCount.Find(x => x.name.Equals(role.Name));
                            ex.CountInc();
                            if (!isOffline) ex.OnlineInc();
                        }
                        catch(Exception e)
                        {
                            mentionsCount.Add(new MentC { count = 1, name = role.Name, online = (isOffline ? 0UL : 1UL) });
                        }
                    }
                }
            }

            mentionsCount.Find(x => x.name.Equals("@everyone")).name = "everyone";

            string text = string.Empty;

            if(pas.Contains("-u"))
            {
                var exitContains = new List<string>();
                foreach(var param in pas)
                {
                    try
                    {
                        exitContains.Add(mentionsCount.Find(x => x.name.Equals(param)).name);
                    }
                    catch (Exception e) { }
                }
                foreach (var res in mentionsCount) if(exitContains.Contains(res.name)) text += (parameters.Length != 0 ? (pas.Contains("-s") ? "@" : "") : "") + res.name + " -> " + res.count + " (" + res.online + ")\n";
            }
            else foreach (var res in mentionsCount) text += (parameters.Length != 0 ? (pas.Contains("-s") ? "@" : "") : "") + res.name + " -> " + res.count + " (" + res.online + ")\n";

            if(text != string.Empty) await ReplyAsync(text);

            GetLog.ToConsole(Context, "Message");
        }
    }
}