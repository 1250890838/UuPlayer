#include "media_item.h"

namespace entities{
MediaItem::MediaItem():id(0),name(),duration(0),albumdata(),artists(),reason(),url(),lyrics()
{

}

MediaItem& MediaItem::operator=(const MediaItem& other) {
  this->id = other.id;
  this->name = other.name;
  this->duration = other.duration;
  this->albumdata = other.albumdata;
  this->artists = other.artists;
  this->reason = other.reason;
  this->url = other.url;
  this->lyrics = other.lyrics;
  return *this;
}
}
