#pragma once

#include <cstdint>
#include <memory>

namespace tf2_bot_detector
{
	enum class KickReason;
	enum class LobbyMemberTeam : uint8_t;
	enum class PlayerAttribute;
	enum class TeamShareResult;
	class IPlayer;
	struct ModerationRule;
	struct PlayerAttributesList;
	struct PlayerMarks;
	class IRCONActionManager;
	class Settings;
	class SteamID;
	class IWorldState;

	class IModeratorLogic
	{
	public:
		virtual ~IModeratorLogic() = default;

		static std::unique_ptr<IModeratorLogic> Create(IWorldState& world, const Settings& settings, IRCONActionManager& actionManager);

		virtual void Update() = 0;

		virtual bool InitiateVotekick(const IPlayer& player, KickReason reason, const PlayerMarks* marks = nullptr) = 0;

		virtual PlayerMarks GetPlayerAttributes(const SteamID& id) const = 0;
		virtual PlayerMarks HasPlayerAttributes(const SteamID& id, const PlayerAttributesList& attributes) const = 0;
		virtual bool SetPlayerAttribute(const IPlayer& player, PlayerAttribute markType, bool set = true) = 0;

		virtual TeamShareResult GetTeamShareResult(const SteamID& id) const = 0;

		virtual const IPlayer* GetBotLeader() const = 0;

		virtual bool IsUserRunningTool(const SteamID& id) const = 0;
		virtual void SetUserRunningTool(const SteamID& id, bool isUserRunningTool = true) = 0;

		virtual size_t GetBlacklistedPlayerCount() const = 0;
		virtual size_t GetRuleCount() const = 0;

		virtual void ReloadConfigFiles() = 0;
	};
}
