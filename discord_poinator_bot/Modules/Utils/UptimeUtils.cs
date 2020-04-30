using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace discord_poinator_bot.Modules.Utils
{
    class UptimeUtils
    {
        private static DateTime dateTime = DateTime.Now;

        public static void Begin()
        {
            dateTime = DateTime.Now;
        }

        public static string GetUptime()
        {
            var thisDate = DateTime.Now;

            var res = thisDate - dateTime;

            return res.Days + " days, " + res.Hours + " hours, " + res.Minutes + " minutes, " + res.Seconds + " seconds";
        }
    }
}
