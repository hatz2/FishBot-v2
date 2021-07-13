# FishBot v2
 Fish SP bot for the MMORPG Nostale written in C++. This version is an improved version of: https://github.com/hatz02/FishBot

 ## Improvements
 * No need to use Bladetiger's packetlogger.
 * It should not crash because of the packetlogger.
 * Overall perfomance should be improved.
 * The bot won't use the EXP skill when you're already at the maximun job level.
 * Start the bot with F5
 * Stop the bot with F8
 * Close the bot with F12
 * It is compatible with other packetloggers or tools that also need to hook the send/recv functions.

 ## How to use it
 You have to ways of injecting the bot:
 1. Use the provided Injector to inject the dll into all the target processes
 2. If you don't want it to be injected on all the processes you can manually inject it with whatever injector you want.
