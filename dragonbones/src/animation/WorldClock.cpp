#include "WorldClock.h"

NAMESPACE_DRAGONBONES_BEGIN

const WorldClock WorldClock::clock;

WorldClock::WorldClock():
    time(0.f),
    timeScale(1.f),
    _animatebles()
{
}
WorldClock::~WorldClock()
{
    clear();
}

bool WorldClock::contains(const IAnimateble* value) const
{
    return std::find(_animatebles.cbegin(), _animatebles.cend(), value) != _animatebles.cend();
}

void WorldClock::add(IAnimateble* value)
{
    if (std::find(_animatebles.begin(), _animatebles.end(), value) == _animatebles.end())
    {
        _animatebles.push_back(value);
    }
}

void WorldClock::remove(IAnimateble* value)
{
    const auto iterator = std::find(_animatebles.begin(), _animatebles.end(), value);
    if (iterator != _animatebles.end())
    {
        *iterator = nullptr;
    }
}

void WorldClock::clear()
{
    for (auto animateble : _animatebles)
    {
        animateble = nullptr;
    }
}

void WorldClock::advanceTime(float passedTime)
{
    if (passedTime < 0 || passedTime != passedTime)
    {
        passedTime = 0;
    }

    passedTime *= timeScale;

    if (passedTime < 0)
    {
        time -= passedTime;
    }
    else
    {
        time += passedTime;
    }

    if (passedTime && !_animatebles.empty())
    {
        std::size_t i = 0, r = 0, l = _animatebles.size();

        for (; i < l; ++i)
        {
            const auto animateble = _animatebles[i];
            if (animateble)
            {
                animateble->advanceTime(passedTime);

                if (r > 0)
                {
                    _animatebles[i - r] = animateble;
                }
            }
            else
            {
                r++;
            }
        }

        if (r > 0)
        {
            l = _animatebles.size();

            for (; i < l; ++i)
            {
                const auto animateble = _animatebles[i];
                if (animateble)
                {
                    _animatebles[i - r] = animateble;
                }
                else
                {
                    r++;
                }
            }

            _animatebles.reserve(l - r);
        }
    }
}

NAMESPACE_DRAGONBONES_END