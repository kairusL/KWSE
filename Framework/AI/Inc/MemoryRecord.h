#pragma once

namespace KWSE::AI
{
	using Property = std::variant <int, float, KWSE::Math::Vector2>;

	struct MemoryRecord
	{
		std::unordered_map<std::string, Property> properties;
		uint64_t entityId = 0;
		float lastRecordedTime = 0.0f;
		float importance = 0.0f;
	};

	using MemoryRecords = std::list<MemoryRecord>;

	inline MemoryRecord& FindOrCreate(MemoryRecords& records, uint64_t uniqueId)
	{
		auto iter = std::find_if(records.begin(), records.end(), [&](const MemoryRecord& record)
		{
			return (record.entityId == uniqueId);
		});

		if (iter==records.end())
		{
			MemoryRecord tempRecord;
			tempRecord.entityId = uniqueId;
			records.push_back(tempRecord);
			iter = --records.end();
		}
		return *iter;
	 }


}