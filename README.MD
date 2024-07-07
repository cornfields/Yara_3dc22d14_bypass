### Simple CobaltStrike YARA 3dc22d14 Bypass
This application is designed to search for and modify a specific hex pattern within .bin files in the application directory. 
It targets the hex pattern "\x25\x73\x20\x61\x73\x20\x25\x73\x5c\x25\x73\x3a\x20\x25\x64", which corresponds to "%s as %s\%s: %d". 
When this pattern is found, the application patches it to "\x25\x73\x20\x2d\x73\x20\x25\x73\x5c\x25\x73\x3a\x20\x25\x64" (%s -s %s%s: %d).

This tool is specifically created to patch CobaltStrike Raw Payload, ensuring that the Windows_Trojan_CobaltStrike_3dc22d14 is effectively bypassed.