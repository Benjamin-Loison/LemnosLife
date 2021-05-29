#ifndef DISCORD_H_INCLUDED
#define DISCORD_H_INCLUDED

#include <string>

bool isDiscordUsernameAssignedFor(std::string igUsername);
void initializeDiscord(), assignDiscordUsernameTo(std::string, std::string), saveDiscord();
std::string getDiscordUsernameFor(std::string);

#endif
