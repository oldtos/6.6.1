/*******************************************************************************
 * retroshare-gui/src/gui/gxschannels/GxsChannelPostsWidget.h                  *
 *                                                                             *
 * Copyright 2013 by Robert Fernie     <retroshare.project@gmail.com>          *
 *                                                                             *
 * This program is free software: you can redistribute it and/or modify        *
 * it under the terms of the GNU Affero General Public License as              *
 * published by the Free Software Foundation, either version 3 of the          *
 * License, or (at your option) any later version.                             *
 *                                                                             *
 * This program is distributed in the hope that it will be useful,             *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                *
 * GNU Affero General Public License for more details.                         *
 *                                                                             *
 * You should have received a copy of the GNU Affero General Public License    *
 * along with this program. If not, see <https://www.gnu.org/licenses/>.       *
 *                                                                             *
 *******************************************************************************/

#ifndef _GXS_CHANNELPOSTSWIDGET_H
#define _GXS_CHANNELPOSTSWIDGET_H

#include <map>

#include "gui/gxs/GxsMessageFramePostWidget.h"

#include "gui/feeds/FeedHolder.h"

namespace Ui {
class GxsChannelPostsWidgetWithModel;
}

class GxsChannelPostItem;
class QTreeWidgetItem;
class FeedItem;
class RsGxsChannelPostsModel;

class GxsChannelPostsWidgetWithModel: public GxsMessageFrameWidget
{
	Q_OBJECT

public:
	/* Filters */
	enum Filter {
		FILTER_TITLE =     1,
		FILTER_MSG =       2,
		FILTER_FILE_NAME = 3
	};

public:
	/** Default Constructor */
	GxsChannelPostsWidgetWithModel(const RsGxsGroupId &channelId, QWidget *parent = 0);
	/** Default Destructor */
	~GxsChannelPostsWidgetWithModel();

	/* GxsMessageFrameWidget */
	virtual QIcon groupIcon();
    virtual void groupIdChanged() { updateDisplay(true); }
    virtual QString groupName(bool) override;
    virtual bool navigate(const RsGxsMessageId&) override;

	void updateDisplay(bool complete);

#ifdef TODO
	/* FeedHolder */
	virtual QScrollArea *getScrollArea();
	virtual void deleteFeedItem(FeedItem *feedItem, uint32_t type);
	virtual void openChat(const RsPeerId& peerId);
#endif
	virtual void openComments(uint32_t type, const RsGxsGroupId &groupId, const QVector<RsGxsMessageId> &msg_versions, const RsGxsMessageId &msgId, const QString &title);

protected:
	/* GxsMessageFramePostWidget */
	virtual void groupNameChanged(const QString &name);
#ifdef TODO
	virtual bool insertGroupData(const RsGxsGenericGroupData *data) override;
#endif
	virtual bool useThread() { return mUseThread; }
    virtual void blank() ;

#ifdef TODO
	virtual bool getGroupData(RsGxsGenericGroupData *& data) override;
    virtual void getMsgData(const std::set<RsGxsMessageId>& msgIds,std::vector<RsGxsGenericMsgData*>& posts) override;
    virtual void getAllMsgData(std::vector<RsGxsGenericMsgData*>& posts) override;
	virtual void insertPosts(const std::vector<RsGxsGenericMsgData*>& posts) override;
	virtual void insertAllPosts(const std::vector<RsGxsGenericMsgData*>& posts, GxsMessageFramePostThread *thread) override;
#endif

	/* GxsMessageFrameWidget */
	virtual void setAllMessagesReadDo(bool read, uint32_t &token);

private slots:
	void updateGroupData();
	void createMsg();
	void toggleAutoDownload();
	void subscribeGroup(bool subscribe);
	void filterChanged(int filter);
	void setViewMode(int viewMode);
	void settingsChanged();

private:
	void processSettings(bool load);

	void setAutoDownload(bool autoDl);
	static bool filterItem(FeedItem *feedItem, const QString &text, int filter);

	int viewMode();

	void insertChannelDetails(const RsGxsChannelGroup &group);
	void handleEvent_main_thread(std::shared_ptr<const RsEvent> event);

private:
	QAction *mAutoDownloadAction;

    RsGxsChannelGroup mGroup;
	bool mUseThread;
    RsEventsHandlerId_t mEventHandlerId ;

    RsGxsChannelPostsModel *mThreadModel;
	UIStateHelper *mStateHelper;

	/* UI - from Designer */
	Ui::GxsChannelPostsWidgetWithModel *ui;
};

#endif
