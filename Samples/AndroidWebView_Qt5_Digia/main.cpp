/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QGuiApplication>
#include <QtQuick/QQuickView>
#include "fboinsgrenderer.h"

// Qt 5.2 bug: this should be included after GUI headers
#include <QtAndroidExtras>
#include <QAndroidJniObject>
#include <QAndroidQPAPluginGap.h>

#include <JniEnvPtr.h>

// SGEXP TODO: this may be useful for some Qt 4 apps
#if defined(Q_OS_ANDROID)
/*bool preloadJavaClasses()
{
	JavaVM * jvm = QAndroidJniEnvironment::javaVM();
	JNIEnv * env = 0;
	if (jvm->AttachCurrentThread(&env, NULL) < 0)
	{
		qCritical("AttachCurrentThread failed!");
		return false;
	}

	JniEnvPtr jep(env);
	jep.PreloadClass("ru/dublgis/offscreenview/OffscreenWebView");
	return true;
}*/
#endif

// SGEXP - temporary code!
// Declaring entry point for nativeJNIPreloadClass so we don't have to register it.
// It must be "C" because the function name should not be mangled.
extern "C" {
	JNIEXPORT void JNICALL Java_ru_dublgis_offscreenview_ClassLoader_nativeJNIPreloadClass(JNIEnv * env, jobject)
	{
		qDebug()<<__FUNCTION__<<"***************************************************";
		JniEnvPtr jep(env);
		jep.PreloadClass("ru/dublgis/offscreenview/OffscreenWebView");
	}
}

int main(int argc, char **argv)
{
	// SGEXP - temporary code!
	QAndroidJniEnvironment jni_thread_attacher; Q_UNUSED(jni_thread_attacher);
	QAndroidJniObject::callStaticMethod<void>(
		"ru/dublgis/offscreenview/ClassLoader",
		"callJNIPreloadClass",
		"(Landroid/app/Activity;)V",
		QAndroidQPAPluginGap::getActivity());

	/*#if defined(Q_OS_ANDROID)
		if (!preloadJavaClasses())
		{
			return -1;
		}
	#endif*/

    QGuiApplication app(argc, argv);

    qmlRegisterType<FboInSGRenderer>("SceneGraphRendering", 1, 0, "Renderer");

    QQuickView view;
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl("qrc:///scenegraph/textureinsgnode/main.qml"));
    view.show();

    return app.exec();
}