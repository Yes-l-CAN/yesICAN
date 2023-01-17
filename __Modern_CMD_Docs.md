https://modern.ircdocs.horse/
---

<!-- '?' == 명시되진 않았는데 아마 이럴거같음 -->
| `command` | `Query` | `example` |
|:---|:---|:---|
|__PASS__|`PASS <password>`|PASS 0000|
|->|`NO REPLY`|
|__NICK__|`NICK <nickname>`|NICK Mike|
|->|`:<source> NICK <nickname>`|-> :yuhwang NICK babo|
|__USER__|`USER <username> 0 * <realname>`|USER yotak 0 * yuje|
|->|`NO REPLY (Welcome protocols 001-004)`|
|__PING__|`PING <token>`|PING hi|
|->|`PONG <server> <token>`|-> PONG PokemonGo hi|
|__QUIT__|`QUIT [<reason>]`|QUIT :it's too boring|
|->|`:<source> QUIT :Quit: <reason>`|-> :yotak QUIT :Quit: IRC sooo EZ|
|__JOIN__|`JOIN <channel>{,<channel>} [<key>{,<key>}]`|JOIN #foo,#bar|
|->|`:<source> JOIN <channel>`|-> :yuhwang JOIN #foo|
|__PART__|`PART <channel>{,<channel>} [<reason>]`|PART #foo,#bar :going to eat something|
|->|`:<source> PART <channel> [<reason>]?`|-> :yuhwang PART #foo|
|__KICK__|`KICK <channel> <user> *( "," <user> ) [<comment>]`|KICK #42seoul yuhwang :too stupid|
|->|`:<source> KICK <channel> <user> [<comment>]?`|-> :yotak KICK #42seoul yuhwang :too stupid|
|__PRIVMSG__|`PRIVMSG <target>{,<target>} <text to be sent>`|PRIVMSG #42seoul,yotak :Hello World!)
|->|`:<source> PRIVMSG <target> :<text>`|-> :yuhwang PRIVMSG yotak :Hello World!)
|__NOTICE__|`NOTICE <target>{,<target>} <text to be sent>`|NOTICE #42seoul,yotak :Hello World!|
|->|`NO REPLY`|
