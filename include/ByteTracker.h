#pragma once
#include <future>
#include <vector>

namespace bytetrack
{
struct Rect
{
    float x{}, y{}, width{}, height{};

    Rect() = default;
    Rect(float x_, float y_, float width_, float height_) 
    : x(x_), y(y_), width(width_), height(height_) {};
};

struct Object
{
    float prob{};
    unsigned int label{};
    Rect rect{};

    Object() = default;
    Object(float prob_, unsigned int label_, Rect rect_) 
    : prob(prob_), label(label_), rect(rect_) {};
};

struct Track
{
    bool b_activated{};
    unsigned long long track_id{};
    unsigned long long frame_id{};
    Object object{};

    Track() = default;
    Track(bool b_activated_, unsigned long long track_id_, unsigned long long frame_id_, Object obj_) 
    : b_activated(b_activated_), track_id(track_id_), frame_id(frame_id_), object(obj_) {};
};


class ByteTrackerImpl;
class ByteTracker
{
public:
    ByteTracker(const unsigned int& max_age=30,                //max lost times
                const float& track_thresh = 0.5,        //higher thresh used for first track, the lower thresh used for second track
                const float& high_thresh = 0.6,         //thresh for init track
                const float& match_thresh = 0.8);       //iou thresh for track match
    ~ByteTracker() = default;
    std::vector<Track> update(const std::vector<Object>& objects);

private:
    std::shared_ptr<ByteTrackerImpl> tracker_impl_;
};

}