/*
 * Mediastreamer2 encoding-filter-impl.h
 * Copyright (C) 2018 Belledonne Communications SARL
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#pragma once

#include "mediastreamer2/msvideo.h"

#include "filter-impl-base.h"

namespace mediastreamer {

class EncodingFilterImpl: public FilterImplBase {
public:
	EncodingFilterImpl(MSFilter *f): FilterImplBase(f) {}

	virtual const MSVideoConfiguration *getVideoConfiguratons() const = 0;
	virtual void setVideoConfigurations(const MSVideoConfiguration *vconfs) = 0;
	virtual int setVideoConfiguration(const MSVideoConfiguration *vconf) = 0;

	virtual int getBitrate() const = 0;
	virtual void setBitrate(int br) = 0;

	virtual float getFps() const = 0;
	virtual void setFps(float  fps) = 0;

	virtual MSVideoSize getVideoSize() const = 0;
	virtual void setVideoSize(const MSVideoSize &vsize) = 0;

	virtual void enableAvpf(bool enable) = 0;

	virtual void notifyPli() = 0;
	virtual void notifyFir() = 0;
};

} // namespace mediastreamer
