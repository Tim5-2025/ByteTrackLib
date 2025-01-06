#include "STrack.h"

#include <cstddef>

namespace bytetrack
{
STrack::STrack(const Object& object) :
    kalman_filter_(),
    mean_(),
    covariance_(),
    object_(object),
    state_(STrackState::New),
    is_activated_(false),
    track_id_(0),
    frame_id_(0),
    start_frame_id_(0),
    tracklet_len_(0)
{
}

STrack::~STrack()
{
}

const Object& STrack::getObject() const
{
    return object_;
}

const STrackState& STrack::getSTrackState() const
{
    return state_;
}

const bool& STrack::isActivated() const
{
    return is_activated_;
}


const size_t& STrack::getTrackId() const
{
    return track_id_;
}

const size_t& STrack::getFrameId() const
{
    return frame_id_;
}

const size_t& STrack::getStartFrameId() const
{
    return start_frame_id_;
}

const size_t& STrack::getTrackletLength() const
{
    return tracklet_len_;
}

KalmanFilter::DetectBox box2Measure(const Rect& rect)
{
    return { rect.x + rect.width / 2,
        rect.y + rect.height / 2,
        rect.width / rect.height,
        rect.height};
}

void STrack::activate(const size_t& frame_id, const size_t& track_id)
{
    kalman_filter_.initiate(mean_, covariance_, box2Measure(object_.rect));

    updateRect();

    state_ = STrackState::Tracked;
    if (frame_id == 1)
    {
        is_activated_ = true;
    }
    track_id_ = track_id;
    frame_id_ = frame_id;
    start_frame_id_ = frame_id;
    tracklet_len_ = 0;
}

void STrack::reActivate(const STrack &new_track, const size_t &frame_id, const int &new_track_id)
{
    kalman_filter_.update(mean_, covariance_, box2Measure(new_track.getObject().rect));

    updateRect();

    state_ = STrackState::Tracked;
    is_activated_ = true;
    object_.prob = new_track.getObject().prob;
    object_.label = new_track.getObject().label;
    if (0 <= new_track_id)
    {
        track_id_ = new_track_id;
    }
    frame_id_ = frame_id;
    tracklet_len_ = 0;
}

void STrack::predict()
{
    if (state_ != STrackState::Tracked)
    {
        mean_[7] = 0;
    }
    kalman_filter_.predict(mean_, covariance_);
}

void STrack::update(const STrack &new_track, const size_t &frame_id)
{
    kalman_filter_.update(mean_, covariance_, box2Measure(new_track.getObject().rect));

    updateRect();

    state_ = STrackState::Tracked;
    is_activated_ = true;
    object_.prob = new_track.getObject().prob;
    object_.label = new_track.getObject().label;
    frame_id_ = frame_id;
    tracklet_len_++;
}

void STrack::markAsLost()
{
    state_ = STrackState::Lost;
}

void STrack::markAsRemoved()
{
    state_ = STrackState::Removed;
}

void STrack::updateRect()
{
    object_.rect.width = mean_[2] * mean_[3];
    object_.rect.height = mean_[3];
    object_.rect.x = mean_[0] - object_.rect.width / 2;
    object_.rect.y = mean_[1] - object_.rect.height / 2;
}

}