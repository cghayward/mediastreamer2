/*
 *  androidvideo_capture_session.h
 *
 *  mediastreamer2 library - modular sound and video processing and streaming
 *  This is the video capture filter for Android using deprecated API android.hardware.Camera.
 *  It uses one of the JNI wrappers to access Android video capture API(5,8,9).
 *
 *  Copyright (C) 2018  Belledonne Communications, Grenoble, France
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef androidvideo_capture_session_include
#define androidvideo_capture_session_include

#include <media/NdkImageReader.h>

namespace AndroidVideo {
class AndroidVideoCaptureSession {
	private:
	ACameraManager *mCameraManager;
	ACameraCaptureSession *mCameraSession1;
	ACameraCaptureSession *mCameraSession2;
	ACameraDevice *mCameraDevice;

	// Window
	ANativeWindow *mWindowImageReader;
	ANativeWindow *mWindowSurfaceView;
	ACameraOutputTarget *mOutputTarget1;
	ACameraOutputTarget *mOutputTarget2;

	// Image Reader
	AImageReader* mImageReader;

	// Session
	ACaptureSessionOutput *mSessionOutput1;
	ACaptureSessionOutput *mSessionOutput2;
	ACaptureSessionOutputContainer *mSessionOutputContainer1;
	ACaptureSessionOutputContainer *mSessionOutputContainer2;
	bool mSessionReady1;
	bool mSessionReady2;
	bool mSessionStop1;
	bool mSessionStop2;
	bool mSessionReset1;
	bool mSessionReset2;

	// Request
	ACaptureRequest *mCaptureRequest1;
	ACaptureRequest *mCaptureRequest2;
	bool mRequestRepeat1;
	bool mRequestRepeat2;

	// Callback
	ACameraDevice_StateCallbacks mDeviceCallback;
	ACameraCaptureSession_stateCallbacks mCaptureSessionCallback;
	ACameraCaptureSession_captureCallbacks mCaptureCallbacks;
	AImageReader_ImageListener mImageCallback;

	public:
		AndroidVideoCaptureSession(AImageReader*);
        AndroidVideoCaptureSession(ANativeWindow*);
		~AndroidVideoCaptureSession();

		// Filter methods
		void videoCaptureInit();
		void videoCapturePreprocess();
		void videoCaptureProcess();
		void videoCapturePostprocess();
		void videoCaptureUninit();

		// Callbacks
		static void onSessionActive(void* context, ACameraCaptureSession *session);
		static void onSessionReady(void* context, ACameraCaptureSession *session);
		static void onSessionClosed(void* context, ACameraCaptureSession *session);
		static void onCaptureSequenceCompleted(void* context, ACameraCaptureSession* session, int sequenceId, int64_t frameNumber);
		static void onImageAvailable(void* context, AImageReader* reader);

		// Other methods
		int videoCaptureSetVsize(void *arg);
		int videoSetNativePreviewWindow(void *arg);
		int videoCaptureSetAutofocus(void *arg);

		void putImage(jbyteArray frame);
	private:
		AndroidVideoCaptureSession(const AndroidVideoCaptureSession&) = delete;
		AndroidVideoCaptureSession() = delete;

		// Helper
		void setImage();

		void initCamera();
		void uninitCamera();

		void initWindow();
		void uninitWindow();

		void initSession();
		void sessionReady(ACameraCaptureSession *session);
		void sessionClosed(ACameraCaptureSession *session);
		void uninitSession();

		void initRequest();
		void uninitRequest();

		camera_status_t checkReturnCameraStatus(camera_status_t status);
		media_status_t checkReturnMediaStatus(media_status_t status);
};
}

#endif // androidvideo_capture_session_include