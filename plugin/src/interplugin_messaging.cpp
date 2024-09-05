/*
 * xPilot: X-Plane pilot client for VATSIM
 * Copyright (C) 2019-2024 Justin Shannon
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see http://www.gnu.org/licenses/.
*/

#include "interplugin_messaging.h"
#include "xpilot.h"

#include "XPLMPlugin.h"

namespace xpilot
{
	static std::string m_inputValue;
	static std::list<InterpluginMessage> m_messageHistory;
	
	void InterpluginMessaging::AddMessage(const std::string& message)
	{
		if (message.empty())
			return;

		InterpluginMessage m;
		m.SetMessage(string_format("[%s] %s", UtcTimestamp().c_str(), message.c_str()));
		m_messageHistory.push_back(m);

		XPLMDebugString(m.GetMessage().c_str());

		/*
		 * By convention, plugin-defined notifications should have 
		 * the high bit set (e.g. be greater or equal to unsigned
		 * 0x8000000) while commands should have this bit be cleared.
		*/

		XPLMSendMessageToPlugin(XPLM_NO_PLUGIN_ID, 
							    0x8534701, 
							    static_cast<void*>(const_cast<char*>(message.data())));
	}

	InterpluginMessaging::InterpluginMessaging(XPilot* instance) :
		m_env(instance)
	{
		;
	}
}
