using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace discord_poinator_bot.Modules.HiLoGame
{
    class HiLo
    {
        private static List<Player> playerList = new List<Player>();
        public static void addAPlayer(ulong playerId, ulong guildId)
        {
            playerList.Add(new Player(playerId, guildId));
        }

        public static Player findAplayer(ulong playerId, ulong guildId)
        {
            return playerList.Find(x => x.PlayerId.Equals(playerId) && x.GuildId.Equals(guildId));
        }

        public static void removePlayer(ulong playerId, ulong guildId)
        {
            var p = playerList.Find(x => x.PlayerId.Equals(playerId) && x.GuildId.Equals(guildId));
            if (p != null)
                playerList.Remove(p);
        }
    }
}
