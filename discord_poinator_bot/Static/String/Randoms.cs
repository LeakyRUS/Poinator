using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Configuration;

namespace discord_poinator_bot.Static.String
{
    class Randoms
    {
        public static string GetString(int swRes)
        {
            string wordsFromXML = ConfigurationManager.AppSettings.Get("_" + (swRes % 21).ToString());

            string[] words = wordsFromXML.Split(new char[] { '|' }, StringSplitOptions.RemoveEmptyEntries);

            return words[new Random((int)DateTime.Now.Ticks).Next(0, words.Length)];
        }
    }
}
