#pragma once

#include "CompensatedTS.h"

#include <filesystem>
#include <memory>
#include <unordered_set>

namespace tf2_bot_detector
{
	class IConsoleLine;
	class IConsoleLineListener;
	class Settings;
	class IWorldState;

	class ConsoleLogParser final
	{
	public:
		ConsoleLogParser(IWorldState& world, const Settings& settings, std::filesystem::path conLogFile);

		void Update();

		float GetParseProgress() const { return m_ParseProgress; }

		const CompensatedTS& GetCurrentTimestamp() const { return m_CurrentTimestamp; }

	private:
		const Settings* m_Settings = nullptr;
		IWorldState* m_WorldState = nullptr;

		void TrySnapshot(bool& snapshotUpdated);
		CompensatedTS m_CurrentTimestamp;

		enum class ParseLineResult
		{
			Unparsed,
			Defer,
			Success,
			Modified,
		};

		using striter = std::string::const_iterator;
		void Parse(bool& linesProcessed, bool& snapshotUpdated, bool& consoleLinesUpdated);
		void ParseChunk(striter& parseEnd, bool& linesProcessed, bool& snapshotUpdated, bool& consoleLinesUpdated);
		bool ParseChatMessage(const std::string_view& lineStr, striter& parseEnd, std::shared_ptr<IConsoleLine>& parsed);

		struct CustomDeleters
		{
			void operator()(FILE*) const;
		};
		std::filesystem::path m_FileName;
		std::unique_ptr<FILE, CustomDeleters> m_File;
		time_point_t m_LastFileLoadAttempt{};
		std::string m_FileLineBuf;
		float m_ParseProgress = 0;
	};
}
