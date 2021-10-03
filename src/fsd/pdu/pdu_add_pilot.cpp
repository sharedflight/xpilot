#include "pdu_add_pilot.h"

PDUAddPilot::PDUAddPilot(QString callsign, QString cid, QString password, NetworkRating rating, ProtocolRevision proto, SimulatorType simType, QString realName) :
    PDUBase(callsign, "")
{
    CID = cid;
    Password = password;
    Rating = rating;
    Protocol = proto;
    SimType = simType;
    RealName = realName;
}

QString PDUAddPilot::Serialize()
{
    QStringList tokens;

    tokens.append("#AP");
    tokens.append(From);
    tokens.append(Delimeter);
    tokens.append(PDUBase::ServerCallsign);
    tokens.append(Delimeter);
    tokens.append(CID);
    tokens.append(Delimeter);
    tokens.append(Password);
    tokens.append(Delimeter);
    tokens.append(toQString(Rating));
    tokens.append(Delimeter);
    tokens.append(toQString(Protocol));
    tokens.append(Delimeter);
    tokens.append(toQString(SimType));
    tokens.append(Delimeter);
    tokens.append(RealName);

    return tokens.join("");
}

PDUAddPilot PDUAddPilot::Parse(QStringList fields)
{
    if(fields.length() < 8)
    {

    }

    return PDUAddPilot(fields[0], fields[2], fields[3], fromQString<NetworkRating>(fields[4]),
            fromQString<ProtocolRevision>(fields[5]), fromQString<SimulatorType>(fields[6]), fields[7]);
}