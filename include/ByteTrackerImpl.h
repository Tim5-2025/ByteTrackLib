#pragma once
#include "STrack.h"
#include "ByteTracker.h"
#include <vector>
#include <future>

namespace bytetrack
{

using STrackPtr = std::shared_ptr<STrack>;

class ByteTrackerImpl
{
public:
    ByteTrackerImpl(const int& max_age,
                const float& track_thresh = 0.5,
                const float& high_thresh = 0.6,
                const float& match_thresh = 0.8);
    ~ByteTrackerImpl();

    std::vector<STrackPtr> update(const std::vector<Object>& objects);

private:
    const float track_thresh_;
    const float high_thresh_;
    const float match_thresh_;
    const size_t max_time_lost_;

    unsigned long long frame_id_;
    unsigned long long track_id_count_;

    std::vector<STrackPtr> tracked_stracks_;
    std::vector<STrackPtr> lost_stracks_;
    // std::vector<STrackPtr> removed_stracks_;
};
}