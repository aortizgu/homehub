/**
 *
 *  Measurement.cc
 *  DO NOT EDIT. This file is generated by drogon_ctl
 *
 */

#include "Measurement.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon_model::sqlite3;

const std::string Measurement::Cols::_tempInterior = "tempInterior";
const std::string Measurement::Cols::_tempExterior = "tempExterior";
const std::string Measurement::Cols::_tempCald = "tempCald";
const std::string Measurement::Cols::_active = "active";
const std::string Measurement::Cols::_date = "date";
const std::string Measurement::Cols::_limitTempConfigured = "limitTempConfigured";
const std::string Measurement::primaryKeyName = "";
const bool Measurement::hasPrimaryKey = false;
const std::string Measurement::tableName = "measurement";

const std::vector<typename Measurement::MetaData> Measurement::metaData_={
{"tempInterior","double","double",8,0,0,1},
{"tempExterior","double","double",8,0,0,1},
{"tempCald","double","double",8,0,0,1},
{"active","uint64_t","integer",8,0,0,1},
{"date","uint64_t","bigint",8,0,0,1},
{"limitTempConfigured","double","double",8,0,0,1}
};
const std::string &Measurement::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
Measurement::Measurement(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["tempInterior"].isNull())
        {
            tempinterior_=std::make_shared<double>(r["tempInterior"].as<double>());
        }
        if(!r["tempExterior"].isNull())
        {
            tempexterior_=std::make_shared<double>(r["tempExterior"].as<double>());
        }
        if(!r["tempCald"].isNull())
        {
            tempcald_=std::make_shared<double>(r["tempCald"].as<double>());
        }
        if(!r["active"].isNull())
        {
            active_=std::make_shared<uint64_t>(r["active"].as<uint64_t>());
        }
        if(!r["date"].isNull())
        {
            date_=std::make_shared<uint64_t>(r["date"].as<uint64_t>());
        }
        if(!r["limitTempConfigured"].isNull())
        {
            limittempconfigured_=std::make_shared<double>(r["limitTempConfigured"].as<double>());
        }
    }
    else
    {
        size_t offset = (size_t)indexOffset;
        if(offset + 6 > r.size())
        {
            LOG_FATAL << "Invalid SQL result for this model";
            return;
        }
        size_t index;
        index = offset + 0;
        if(!r[index].isNull())
        {
            tempinterior_=std::make_shared<double>(r[index].as<double>());
        }
        index = offset + 1;
        if(!r[index].isNull())
        {
            tempexterior_=std::make_shared<double>(r[index].as<double>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            tempcald_=std::make_shared<double>(r[index].as<double>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            active_=std::make_shared<uint64_t>(r[index].as<uint64_t>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            date_=std::make_shared<uint64_t>(r[index].as<uint64_t>());
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            limittempconfigured_=std::make_shared<double>(r[index].as<double>());
        }
    }

}

Measurement::Measurement(const Json::Value &pJson, const std::vector<std::string> &pMasqueradingVector) noexcept(false)
{
    if(pMasqueradingVector.size() != 6)
    {
        LOG_ERROR << "Bad masquerading vector";
        return;
    }
    if(!pMasqueradingVector[0].empty() && pJson.isMember(pMasqueradingVector[0]))
    {
        dirtyFlag_[0] = true;
        if(!pJson[pMasqueradingVector[0]].isNull())
        {
            tempinterior_=std::make_shared<double>(pJson[pMasqueradingVector[0]].asDouble());
        }
    }
    if(!pMasqueradingVector[1].empty() && pJson.isMember(pMasqueradingVector[1]))
    {
        dirtyFlag_[1] = true;
        if(!pJson[pMasqueradingVector[1]].isNull())
        {
            tempexterior_=std::make_shared<double>(pJson[pMasqueradingVector[1]].asDouble());
        }
    }
    if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
    {
        dirtyFlag_[2] = true;
        if(!pJson[pMasqueradingVector[2]].isNull())
        {
            tempcald_=std::make_shared<double>(pJson[pMasqueradingVector[2]].asDouble());
        }
    }
    if(!pMasqueradingVector[3].empty() && pJson.isMember(pMasqueradingVector[3]))
    {
        dirtyFlag_[3] = true;
        if(!pJson[pMasqueradingVector[3]].isNull())
        {
            active_=std::make_shared<uint64_t>((uint64_t)pJson[pMasqueradingVector[3]].asUInt64());
        }
    }
    if(!pMasqueradingVector[4].empty() && pJson.isMember(pMasqueradingVector[4]))
    {
        dirtyFlag_[4] = true;
        if(!pJson[pMasqueradingVector[4]].isNull())
        {
            date_=std::make_shared<uint64_t>((uint64_t)pJson[pMasqueradingVector[4]].asUInt64());
        }
    }
    if(!pMasqueradingVector[5].empty() && pJson.isMember(pMasqueradingVector[5]))
    {
        dirtyFlag_[5] = true;
        if(!pJson[pMasqueradingVector[5]].isNull())
        {
            limittempconfigured_=std::make_shared<double>(pJson[pMasqueradingVector[5]].asDouble());
        }
    }
}

Measurement::Measurement(const Json::Value &pJson) noexcept(false)
{
    if(pJson.isMember("tempInterior"))
    {
        dirtyFlag_[0]=true;
        if(!pJson["tempInterior"].isNull())
        {
            tempinterior_=std::make_shared<double>(pJson["tempInterior"].asDouble());
        }
    }
    if(pJson.isMember("tempExterior"))
    {
        dirtyFlag_[1]=true;
        if(!pJson["tempExterior"].isNull())
        {
            tempexterior_=std::make_shared<double>(pJson["tempExterior"].asDouble());
        }
    }
    if(pJson.isMember("tempCald"))
    {
        dirtyFlag_[2]=true;
        if(!pJson["tempCald"].isNull())
        {
            tempcald_=std::make_shared<double>(pJson["tempCald"].asDouble());
        }
    }
    if(pJson.isMember("active"))
    {
        dirtyFlag_[3]=true;
        if(!pJson["active"].isNull())
        {
            active_=std::make_shared<uint64_t>((uint64_t)pJson["active"].asUInt64());
        }
    }
    if(pJson.isMember("date"))
    {
        dirtyFlag_[4]=true;
        if(!pJson["date"].isNull())
        {
            date_=std::make_shared<uint64_t>((uint64_t)pJson["date"].asUInt64());
        }
    }
    if(pJson.isMember("limitTempConfigured"))
    {
        dirtyFlag_[5]=true;
        if(!pJson["limitTempConfigured"].isNull())
        {
            limittempconfigured_=std::make_shared<double>(pJson["limitTempConfigured"].asDouble());
        }
    }
}

void Measurement::updateByMasqueradedJson(const Json::Value &pJson,
                                            const std::vector<std::string> &pMasqueradingVector) noexcept(false)
{
    if(pMasqueradingVector.size() != 6)
    {
        LOG_ERROR << "Bad masquerading vector";
        return;
    }
    if(!pMasqueradingVector[0].empty() && pJson.isMember(pMasqueradingVector[0]))
    {
        dirtyFlag_[0] = true;
        if(!pJson[pMasqueradingVector[0]].isNull())
        {
            tempinterior_=std::make_shared<double>(pJson[pMasqueradingVector[0]].asDouble());
        }
    }
    if(!pMasqueradingVector[1].empty() && pJson.isMember(pMasqueradingVector[1]))
    {
        dirtyFlag_[1] = true;
        if(!pJson[pMasqueradingVector[1]].isNull())
        {
            tempexterior_=std::make_shared<double>(pJson[pMasqueradingVector[1]].asDouble());
        }
    }
    if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
    {
        dirtyFlag_[2] = true;
        if(!pJson[pMasqueradingVector[2]].isNull())
        {
            tempcald_=std::make_shared<double>(pJson[pMasqueradingVector[2]].asDouble());
        }
    }
    if(!pMasqueradingVector[3].empty() && pJson.isMember(pMasqueradingVector[3]))
    {
        dirtyFlag_[3] = true;
        if(!pJson[pMasqueradingVector[3]].isNull())
        {
            active_=std::make_shared<uint64_t>((uint64_t)pJson[pMasqueradingVector[3]].asUInt64());
        }
    }
    if(!pMasqueradingVector[4].empty() && pJson.isMember(pMasqueradingVector[4]))
    {
        dirtyFlag_[4] = true;
        if(!pJson[pMasqueradingVector[4]].isNull())
        {
            date_=std::make_shared<uint64_t>((uint64_t)pJson[pMasqueradingVector[4]].asUInt64());
        }
    }
    if(!pMasqueradingVector[5].empty() && pJson.isMember(pMasqueradingVector[5]))
    {
        dirtyFlag_[5] = true;
        if(!pJson[pMasqueradingVector[5]].isNull())
        {
            limittempconfigured_=std::make_shared<double>(pJson[pMasqueradingVector[5]].asDouble());
        }
    }
}
                                                                    
void Measurement::updateByJson(const Json::Value &pJson) noexcept(false)
{
    if(pJson.isMember("tempInterior"))
    {
        dirtyFlag_[0] = true;
        if(!pJson["tempInterior"].isNull())
        {
            tempinterior_=std::make_shared<double>(pJson["tempInterior"].asDouble());
        }
    }
    if(pJson.isMember("tempExterior"))
    {
        dirtyFlag_[1] = true;
        if(!pJson["tempExterior"].isNull())
        {
            tempexterior_=std::make_shared<double>(pJson["tempExterior"].asDouble());
        }
    }
    if(pJson.isMember("tempCald"))
    {
        dirtyFlag_[2] = true;
        if(!pJson["tempCald"].isNull())
        {
            tempcald_=std::make_shared<double>(pJson["tempCald"].asDouble());
        }
    }
    if(pJson.isMember("active"))
    {
        dirtyFlag_[3] = true;
        if(!pJson["active"].isNull())
        {
            active_=std::make_shared<uint64_t>((uint64_t)pJson["active"].asUInt64());
        }
    }
    if(pJson.isMember("date"))
    {
        dirtyFlag_[4] = true;
        if(!pJson["date"].isNull())
        {
            date_=std::make_shared<uint64_t>((uint64_t)pJson["date"].asUInt64());
        }
    }
    if(pJson.isMember("limitTempConfigured"))
    {
        dirtyFlag_[5] = true;
        if(!pJson["limitTempConfigured"].isNull())
        {
            limittempconfigured_=std::make_shared<double>(pJson["limitTempConfigured"].asDouble());
        }
    }
}

const double &Measurement::getValueOfTempinterior() const noexcept
{
    const static double defaultValue = double();
    if(tempinterior_)
        return *tempinterior_;
    return defaultValue;
}
const std::shared_ptr<double> &Measurement::getTempinterior() const noexcept
{
    return tempinterior_;
}
void Measurement::setTempinterior(const double &pTempinterior) noexcept
{
    tempinterior_ = std::make_shared<double>(pTempinterior);
    dirtyFlag_[0] = true;
}




const double &Measurement::getValueOfTempexterior() const noexcept
{
    const static double defaultValue = double();
    if(tempexterior_)
        return *tempexterior_;
    return defaultValue;
}
const std::shared_ptr<double> &Measurement::getTempexterior() const noexcept
{
    return tempexterior_;
}
void Measurement::setTempexterior(const double &pTempexterior) noexcept
{
    tempexterior_ = std::make_shared<double>(pTempexterior);
    dirtyFlag_[1] = true;
}




const double &Measurement::getValueOfTempcald() const noexcept
{
    const static double defaultValue = double();
    if(tempcald_)
        return *tempcald_;
    return defaultValue;
}
const std::shared_ptr<double> &Measurement::getTempcald() const noexcept
{
    return tempcald_;
}
void Measurement::setTempcald(const double &pTempcald) noexcept
{
    tempcald_ = std::make_shared<double>(pTempcald);
    dirtyFlag_[2] = true;
}




const uint64_t &Measurement::getValueOfActive() const noexcept
{
    const static uint64_t defaultValue = uint64_t();
    if(active_)
        return *active_;
    return defaultValue;
}
const std::shared_ptr<uint64_t> &Measurement::getActive() const noexcept
{
    return active_;
}
void Measurement::setActive(const uint64_t &pActive) noexcept
{
    active_ = std::make_shared<uint64_t>(pActive);
    dirtyFlag_[3] = true;
}




const uint64_t &Measurement::getValueOfDate() const noexcept
{
    const static uint64_t defaultValue = uint64_t();
    if(date_)
        return *date_;
    return defaultValue;
}
const std::shared_ptr<uint64_t> &Measurement::getDate() const noexcept
{
    return date_;
}
void Measurement::setDate(const uint64_t &pDate) noexcept
{
    date_ = std::make_shared<uint64_t>(pDate);
    dirtyFlag_[4] = true;
}




const double &Measurement::getValueOfLimittempconfigured() const noexcept
{
    const static double defaultValue = double();
    if(limittempconfigured_)
        return *limittempconfigured_;
    return defaultValue;
}
const std::shared_ptr<double> &Measurement::getLimittempconfigured() const noexcept
{
    return limittempconfigured_;
}
void Measurement::setLimittempconfigured(const double &pLimittempconfigured) noexcept
{
    limittempconfigured_ = std::make_shared<double>(pLimittempconfigured);
    dirtyFlag_[5] = true;
}




void Measurement::updateId(const uint64_t id)
{
}

const std::vector<std::string> &Measurement::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "tempInterior",
        "tempExterior",
        "tempCald",
        "active",
        "date",
        "limitTempConfigured"
    };
    return inCols;
}

void Measurement::outputArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(dirtyFlag_[0])
    {
        if(getTempinterior())
        {
            binder << getValueOfTempinterior();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[1])
    {
        if(getTempexterior())
        {
            binder << getValueOfTempexterior();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getTempcald())
        {
            binder << getValueOfTempcald();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getActive())
        {
            binder << getValueOfActive();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getDate())
        {
            binder << getValueOfDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getLimittempconfigured())
        {
            binder << getValueOfLimittempconfigured();
        }
        else
        {
            binder << nullptr;
        }
    }
}

const std::vector<std::string> Measurement::updateColumns() const
{
    std::vector<std::string> ret;
    if(dirtyFlag_[0])
    {
        ret.push_back(getColumnName(0));
    }
    if(dirtyFlag_[1])
    {
        ret.push_back(getColumnName(1));
    }
    if(dirtyFlag_[2])
    {
        ret.push_back(getColumnName(2));
    }
    if(dirtyFlag_[3])
    {
        ret.push_back(getColumnName(3));
    }
    if(dirtyFlag_[4])
    {
        ret.push_back(getColumnName(4));
    }
    if(dirtyFlag_[5])
    {
        ret.push_back(getColumnName(5));
    }
    return ret;
}

void Measurement::updateArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(dirtyFlag_[0])
    {
        if(getTempinterior())
        {
            binder << getValueOfTempinterior();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[1])
    {
        if(getTempexterior())
        {
            binder << getValueOfTempexterior();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getTempcald())
        {
            binder << getValueOfTempcald();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[3])
    {
        if(getActive())
        {
            binder << getValueOfActive();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[4])
    {
        if(getDate())
        {
            binder << getValueOfDate();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[5])
    {
        if(getLimittempconfigured())
        {
            binder << getValueOfLimittempconfigured();
        }
        else
        {
            binder << nullptr;
        }
    }
}
Json::Value Measurement::toJson() const
{
    Json::Value ret;
    if(getTempinterior())
    {
        ret["tempInterior"]=getValueOfTempinterior();
    }
    else
    {
        ret["tempInterior"]=Json::Value();
    }
    if(getTempexterior())
    {
        ret["tempExterior"]=getValueOfTempexterior();
    }
    else
    {
        ret["tempExterior"]=Json::Value();
    }
    if(getTempcald())
    {
        ret["tempCald"]=getValueOfTempcald();
    }
    else
    {
        ret["tempCald"]=Json::Value();
    }
    if(getActive())
    {
        ret["active"]=(Json::UInt64)getValueOfActive();
    }
    else
    {
        ret["active"]=Json::Value();
    }
    if(getDate())
    {
        ret["date"]=(Json::UInt64)getValueOfDate();
    }
    else
    {
        ret["date"]=Json::Value();
    }
    if(getLimittempconfigured())
    {
        ret["limitTempConfigured"]=getValueOfLimittempconfigured();
    }
    else
    {
        ret["limitTempConfigured"]=Json::Value();
    }
    return ret;
}

Json::Value Measurement::toMasqueradedJson(
    const std::vector<std::string> &pMasqueradingVector) const
{
    Json::Value ret;
    if(pMasqueradingVector.size() == 6)
    {
        if(!pMasqueradingVector[0].empty())
        {
            if(getTempinterior())
            {
                ret[pMasqueradingVector[0]]=getValueOfTempinterior();
            }
            else
            {
                ret[pMasqueradingVector[0]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[1].empty())
        {
            if(getTempexterior())
            {
                ret[pMasqueradingVector[1]]=getValueOfTempexterior();
            }
            else
            {
                ret[pMasqueradingVector[1]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[2].empty())
        {
            if(getTempcald())
            {
                ret[pMasqueradingVector[2]]=getValueOfTempcald();
            }
            else
            {
                ret[pMasqueradingVector[2]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[3].empty())
        {
            if(getActive())
            {
                ret[pMasqueradingVector[3]]=(Json::UInt64)getValueOfActive();
            }
            else
            {
                ret[pMasqueradingVector[3]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[4].empty())
        {
            if(getDate())
            {
                ret[pMasqueradingVector[4]]=(Json::UInt64)getValueOfDate();
            }
            else
            {
                ret[pMasqueradingVector[4]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[5].empty())
        {
            if(getLimittempconfigured())
            {
                ret[pMasqueradingVector[5]]=getValueOfLimittempconfigured();
            }
            else
            {
                ret[pMasqueradingVector[5]]=Json::Value();
            }
        }
        return ret;
    }
    LOG_ERROR << "Masquerade failed";
    if(getTempinterior())
    {
        ret["tempInterior"]=getValueOfTempinterior();
    }
    else
    {
        ret["tempInterior"]=Json::Value();
    }
    if(getTempexterior())
    {
        ret["tempExterior"]=getValueOfTempexterior();
    }
    else
    {
        ret["tempExterior"]=Json::Value();
    }
    if(getTempcald())
    {
        ret["tempCald"]=getValueOfTempcald();
    }
    else
    {
        ret["tempCald"]=Json::Value();
    }
    if(getActive())
    {
        ret["active"]=(Json::UInt64)getValueOfActive();
    }
    else
    {
        ret["active"]=Json::Value();
    }
    if(getDate())
    {
        ret["date"]=(Json::UInt64)getValueOfDate();
    }
    else
    {
        ret["date"]=Json::Value();
    }
    if(getLimittempconfigured())
    {
        ret["limitTempConfigured"]=getValueOfLimittempconfigured();
    }
    else
    {
        ret["limitTempConfigured"]=Json::Value();
    }
    return ret;
}

bool Measurement::validateJsonForCreation(const Json::Value &pJson, std::string &err)
{
    if(pJson.isMember("tempInterior"))
    {
        if(!validJsonOfField(0, "tempInterior", pJson["tempInterior"], err, true))
            return false;
    }
    if(pJson.isMember("tempExterior"))
    {
        if(!validJsonOfField(1, "tempExterior", pJson["tempExterior"], err, true))
            return false;
    }
    if(pJson.isMember("tempCald"))
    {
        if(!validJsonOfField(2, "tempCald", pJson["tempCald"], err, true))
            return false;
    }
    if(pJson.isMember("active"))
    {
        if(!validJsonOfField(3, "active", pJson["active"], err, true))
            return false;
    }
    if(pJson.isMember("date"))
    {
        if(!validJsonOfField(4, "date", pJson["date"], err, true))
            return false;
    }
    if(pJson.isMember("limitTempConfigured"))
    {
        if(!validJsonOfField(5, "limitTempConfigured", pJson["limitTempConfigured"], err, true))
            return false;
    }
    return true;
}
bool Measurement::validateMasqueradedJsonForCreation(const Json::Value &pJson,
                                                     const std::vector<std::string> &pMasqueradingVector,
                                                     std::string &err)
{
    if(pMasqueradingVector.size() != 6)
    {
        err = "Bad masquerading vector";
        return false;
    }
    if(!pMasqueradingVector[0].empty())
    {
        if(pJson.isMember(pMasqueradingVector[0]))
        {
            if(!validJsonOfField(0, pMasqueradingVector[0], pJson[pMasqueradingVector[0]], err, true))
                return false;
        }
    }
    if(!pMasqueradingVector[1].empty())
    {
        if(pJson.isMember(pMasqueradingVector[1]))
        {
            if(!validJsonOfField(1, pMasqueradingVector[1], pJson[pMasqueradingVector[1]], err, true))
                return false;
        }
    }
    if(!pMasqueradingVector[2].empty())
    {
        if(pJson.isMember(pMasqueradingVector[2]))
        {
            if(!validJsonOfField(2, pMasqueradingVector[2], pJson[pMasqueradingVector[2]], err, true))
                return false;
        }
    }
    if(!pMasqueradingVector[3].empty())
    {
        if(pJson.isMember(pMasqueradingVector[3]))
        {
            if(!validJsonOfField(3, pMasqueradingVector[3], pJson[pMasqueradingVector[3]], err, true))
                return false;
        }
    }
    if(!pMasqueradingVector[4].empty())
    {
        if(pJson.isMember(pMasqueradingVector[4]))
        {
            if(!validJsonOfField(4, pMasqueradingVector[4], pJson[pMasqueradingVector[4]], err, true))
                return false;
        }
    }
    if(!pMasqueradingVector[5].empty())
    {
        if(pJson.isMember(pMasqueradingVector[5]))
        {
            if(!validJsonOfField(5, pMasqueradingVector[5], pJson[pMasqueradingVector[5]], err, true))
                return false;
        }
    }
    return true;
}
bool Measurement::validateJsonForUpdate(const Json::Value &pJson, std::string &err)
{
    if(pJson.isMember("tempInterior"))
    {
        if(!validJsonOfField(0, "tempInterior", pJson["tempInterior"], err, false))
            return false;
    }
    if(pJson.isMember("tempExterior"))
    {
        if(!validJsonOfField(1, "tempExterior", pJson["tempExterior"], err, false))
            return false;
    }
    if(pJson.isMember("tempCald"))
    {
        if(!validJsonOfField(2, "tempCald", pJson["tempCald"], err, false))
            return false;
    }
    if(pJson.isMember("active"))
    {
        if(!validJsonOfField(3, "active", pJson["active"], err, false))
            return false;
    }
    if(pJson.isMember("date"))
    {
        if(!validJsonOfField(4, "date", pJson["date"], err, false))
            return false;
    }
    if(pJson.isMember("limitTempConfigured"))
    {
        if(!validJsonOfField(5, "limitTempConfigured", pJson["limitTempConfigured"], err, false))
            return false;
    }
    return true;
}
bool Measurement::validateMasqueradedJsonForUpdate(const Json::Value &pJson,
                                                   const std::vector<std::string> &pMasqueradingVector,
                                                   std::string &err)
{
    if(pMasqueradingVector.size() != 6)
    {
        err = "Bad masquerading vector";
        return false;
    }
    if(!pMasqueradingVector[0].empty() && pJson.isMember(pMasqueradingVector[0]))
    {
        if(!validJsonOfField(0, pMasqueradingVector[0], pJson[pMasqueradingVector[0]], err, false))
            return false;
    }
    if(!pMasqueradingVector[1].empty() && pJson.isMember(pMasqueradingVector[1]))
    {
        if(!validJsonOfField(1, pMasqueradingVector[1], pJson[pMasqueradingVector[1]], err, false))
            return false;
    }
    if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
    {
        if(!validJsonOfField(2, pMasqueradingVector[2], pJson[pMasqueradingVector[2]], err, false))
            return false;
    }
    if(!pMasqueradingVector[3].empty() && pJson.isMember(pMasqueradingVector[3]))
    {
        if(!validJsonOfField(3, pMasqueradingVector[3], pJson[pMasqueradingVector[3]], err, false))
            return false;
    }
    if(!pMasqueradingVector[4].empty() && pJson.isMember(pMasqueradingVector[4]))
    {
        if(!validJsonOfField(4, pMasqueradingVector[4], pJson[pMasqueradingVector[4]], err, false))
            return false;
    }
    if(!pMasqueradingVector[5].empty() && pJson.isMember(pMasqueradingVector[5]))
    {
        if(!validJsonOfField(5, pMasqueradingVector[5], pJson[pMasqueradingVector[5]], err, false))
            return false;
    }
    return true;
}
bool Measurement::validJsonOfField(size_t index,
                                   const std::string &fieldName,
                                   const Json::Value &pJson, 
                                   std::string &err, 
                                   bool isForCreation)
{
    switch(index)
    {
        case 0:
            if(pJson.isNull())
            {
                err="The " + fieldName + " column cannot be null";
                return false;
            }
            if(!pJson.isNumeric())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            break;
        case 1:
            if(pJson.isNull())
            {
                err="The " + fieldName + " column cannot be null";
                return false;
            }
            if(!pJson.isNumeric())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            break;
        case 2:
            if(pJson.isNull())
            {
                err="The " + fieldName + " column cannot be null";
                return false;
            }
            if(!pJson.isNumeric())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            break;
        case 3:
            if(pJson.isNull())
            {
                err="The " + fieldName + " column cannot be null";
                return false;
            }
            if(!pJson.isUInt64())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            break;
        case 4:
            if(pJson.isNull())
            {
                err="The " + fieldName + " column cannot be null";
                return false;
            }
            if(!pJson.isUInt64())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            break;
        case 5:
            if(pJson.isNull())
            {
                err="The " + fieldName + " column cannot be null";
                return false;
            }
            if(!pJson.isNumeric())
            {
                err="Type error in the "+fieldName+" field";
                return false;
            }
            break;
     
        default:
            err="Internal error in the server";
            return false;
            break;
    }
    return true;
}