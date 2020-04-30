using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace discord_poinator_bot.Modules.HiLoGame
{
    class Player
    {
        public enum Status
        {
            low,
            high,
            win,
            lose
        }

        // Id игрока
        private ulong playerId;

        // Id гильдии
        private ulong guildId;

        // текущая попытка
        private int lastTry;

        // загаданное игроку число
        private int answer;

        public Player(ulong playerId, ulong guildId)
        {
            this.playerId = playerId;
            this.guildId = guildId;
            this.lastTry = 0;
            this.answer = (new Random()).Next(1, 101);
        }

        public ulong PlayerId { get { return this.playerId; } }

        public ulong GuildId { get { return this.guildId; } }

        public int TryesLeft { get { return this.lastTry; } }

        public int Answer {  get { return this.answer;  } }

        public Status decreaseTry(int userTry)
        {
            lastTry++;

            if(userTry > answer)
                return Status.high;
            else if(userTry < answer)
                return Status.low;
            else
                return Status.win;
        }
    }
}
