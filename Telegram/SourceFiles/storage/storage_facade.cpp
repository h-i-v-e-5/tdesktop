/*
This file is part of Telegram Desktop,
the official desktop version of Telegram messaging app, see https://telegram.org

Telegram Desktop is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

It is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

In addition, as a special exception, the copyright holders give permission
to link the code of portions of this program with the OpenSSL library.

Full license: https://github.com/telegramdesktop/tdesktop/blob/master/LICENSE
Copyright (c) 2014-2017 John Preston, https://desktop.telegram.org
*/
#include "storage/storage_facade.h"

#include "storage/storage_shared_media.h"
#include "storage/storage_user_photos.h"

namespace Storage {

class Facade::Impl {
public:
	void add(SharedMediaAddNew &&query);
	void add(SharedMediaAddExisting &&query);
	void add(SharedMediaAddSlice &&query);
	void remove(SharedMediaRemoveOne &&query);
	void remove(SharedMediaRemoveAll &&query);
	void query(
		SharedMediaQuery &&query,
		base::lambda_once<void(SharedMediaResult&&)> &&callback);

	base::Observable<SharedMediaSliceUpdate> &sharedMediaSliceUpdated();
	base::Observable<SharedMediaRemoveOne> &sharedMediaOneRemoved();
	base::Observable<SharedMediaRemoveAll> &sharedMediaAllRemoved();

	void add(UserPhotosAddNew &&query);
	void add(UserPhotosAddSlice &&query);
	void remove(UserPhotosRemoveOne &&query);
	void remove(UserPhotosRemoveAfter &&query);
	rpl::producer<UserPhotosResult> query(UserPhotosQuery &&query) const;

	rpl::producer<UserPhotosSliceUpdate> userPhotosSliceUpdated() const;

private:
	SharedMedia _sharedMedia;
	UserPhotos _userPhotos;

};

void Facade::Impl::add(SharedMediaAddNew &&query) {
	_sharedMedia.add(std::move(query));
}

void Facade::Impl::add(SharedMediaAddExisting &&query) {
	_sharedMedia.add(std::move(query));
}

void Facade::Impl::add(SharedMediaAddSlice &&query) {
	_sharedMedia.add(std::move(query));
}

void Facade::Impl::remove(SharedMediaRemoveOne &&query) {
	_sharedMedia.remove(std::move(query));
}

void Facade::Impl::remove(SharedMediaRemoveAll &&query) {
	_sharedMedia.remove(std::move(query));
}

void Facade::Impl::query(
		SharedMediaQuery &&query,
		base::lambda_once<void(SharedMediaResult&&)> &&callback) {
	_sharedMedia.query(query, std::move(callback));
}

base::Observable<SharedMediaSliceUpdate> &Facade::Impl::sharedMediaSliceUpdated() {
	return _sharedMedia.sliceUpdated;
}

base::Observable<SharedMediaRemoveOne> &Facade::Impl::sharedMediaOneRemoved() {
	return _sharedMedia.oneRemoved;
}

base::Observable<SharedMediaRemoveAll> &Facade::Impl::sharedMediaAllRemoved() {
	return _sharedMedia.allRemoved;
}

void Facade::Impl::add(UserPhotosAddNew &&query) {
	return _userPhotos.add(std::move(query));
}

void Facade::Impl::add(UserPhotosAddSlice &&query) {
	return _userPhotos.add(std::move(query));
}

void Facade::Impl::remove(UserPhotosRemoveOne &&query) {
	return _userPhotos.remove(std::move(query));
}

void Facade::Impl::remove(UserPhotosRemoveAfter &&query) {
	return _userPhotos.remove(std::move(query));
}

rpl::producer<UserPhotosResult> Facade::Impl::query(UserPhotosQuery &&query) const {
	return _userPhotos.query(std::move(query));
}

rpl::producer<UserPhotosSliceUpdate> Facade::Impl::userPhotosSliceUpdated() const {
	return _userPhotos.sliceUpdated();
}

Facade::Facade() : _impl(std::make_unique<Impl>()) {
}

void Facade::add(SharedMediaAddNew &&query) {
	_impl->add(std::move(query));
}

void Facade::add(SharedMediaAddExisting &&query) {
	_impl->add(std::move(query));
}

void Facade::add(SharedMediaAddSlice &&query) {
	_impl->add(std::move(query));
}

void Facade::remove(SharedMediaRemoveOne &&query) {
	_impl->remove(std::move(query));
}

void Facade::remove(SharedMediaRemoveAll &&query) {
	_impl->remove(std::move(query));
}

void Facade::query(
		SharedMediaQuery &&query,
		base::lambda_once<void(SharedMediaResult&&)> &&callback) {
	_impl->query(std::move(query), std::move(callback));
}

base::Observable<SharedMediaSliceUpdate> &Facade::sharedMediaSliceUpdated() {
	return _impl->sharedMediaSliceUpdated();
}

base::Observable<SharedMediaRemoveOne> &Facade::sharedMediaOneRemoved() {
	return _impl->sharedMediaOneRemoved();
}

base::Observable<SharedMediaRemoveAll> &Facade::sharedMediaAllRemoved() {
	return _impl->sharedMediaAllRemoved();
}

void Facade::add(UserPhotosAddNew &&query) {
	return _impl->add(std::move(query));
}

void Facade::add(UserPhotosAddSlice &&query) {
	return _impl->add(std::move(query));
}

void Facade::remove(UserPhotosRemoveOne &&query) {
	return _impl->remove(std::move(query));
}

void Facade::remove(UserPhotosRemoveAfter &&query) {
	return _impl->remove(std::move(query));
}

rpl::producer<UserPhotosResult> Facade::query(UserPhotosQuery &&query) const {
	return _impl->query(std::move(query));
}

rpl::producer<UserPhotosSliceUpdate> Facade::userPhotosSliceUpdated() const {
	return _impl->userPhotosSliceUpdated();
}

Facade::~Facade() = default;

} // namespace Storage