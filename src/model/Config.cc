/**
 *
 *  Config.cc
 *  DO NOT EDIT. This file is generated by drogon_ctl
 *
 */

#include "Config.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon_model::sqlite3;

const std::string Config::Cols::_limitTemp = "limitTemp";
const std::string Config::Cols::_hysteresis = "hysteresis";
const std::string Config::Cols::_id = "id";
const std::string Config::primaryKeyName = "id";
const bool Config::hasPrimaryKey = true;
const std::string Config::tableName = "config";

const std::vector<typename Config::MetaData> Config::metaData_={
{"limitTemp","double","double",8,0,0,1},
{"hysteresis","double","double",8,0,0,1},
{"id","uint64_t","integer",8,0,1,1}
};
const std::string &Config::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
Config::Config(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["limitTemp"].isNull())
        {
            limittemp_=std::make_shared<double>(r["limitTemp"].as<double>());
        }
        if(!r["hysteresis"].isNull())
        {
            hysteresis_=std::make_shared<double>(r["hysteresis"].as<double>());
        }
        if(!r["id"].isNull())
        {
            id_=std::make_shared<uint64_t>(r["id"].as<uint64_t>());
        }
    }
    else
    {
        size_t offset = (size_t)indexOffset;
        if(offset + 3 > r.size())
        {
            LOG_FATAL << "Invalid SQL result for this model";
            return;
        }
        size_t index;
        index = offset + 0;
        if(!r[index].isNull())
        {
            limittemp_=std::make_shared<double>(r[index].as<double>());
        }
        index = offset + 1;
        if(!r[index].isNull())
        {
            hysteresis_=std::make_shared<double>(r[index].as<double>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            id_=std::make_shared<uint64_t>(r[index].as<uint64_t>());
        }
    }

}

Config::Config(const Json::Value &pJson, const std::vector<std::string> &pMasqueradingVector) noexcept(false)
{
    if(pMasqueradingVector.size() != 3)
    {
        LOG_ERROR << "Bad masquerading vector";
        return;
    }
    if(!pMasqueradingVector[0].empty() && pJson.isMember(pMasqueradingVector[0]))
    {
        dirtyFlag_[0] = true;
        if(!pJson[pMasqueradingVector[0]].isNull())
        {
            limittemp_=std::make_shared<double>(pJson[pMasqueradingVector[0]].asDouble());
        }
    }
    if(!pMasqueradingVector[1].empty() && pJson.isMember(pMasqueradingVector[1]))
    {
        dirtyFlag_[1] = true;
        if(!pJson[pMasqueradingVector[1]].isNull())
        {
            hysteresis_=std::make_shared<double>(pJson[pMasqueradingVector[1]].asDouble());
        }
    }
    if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
    {
        dirtyFlag_[2] = true;
        if(!pJson[pMasqueradingVector[2]].isNull())
        {
            id_=std::make_shared<uint64_t>((uint64_t)pJson[pMasqueradingVector[2]].asUInt64());
        }
    }
}

Config::Config(const Json::Value &pJson) noexcept(false)
{
    if(pJson.isMember("limitTemp"))
    {
        dirtyFlag_[0]=true;
        if(!pJson["limitTemp"].isNull())
        {
            limittemp_=std::make_shared<double>(pJson["limitTemp"].asDouble());
        }
    }
    if(pJson.isMember("hysteresis"))
    {
        dirtyFlag_[1]=true;
        if(!pJson["hysteresis"].isNull())
        {
            hysteresis_=std::make_shared<double>(pJson["hysteresis"].asDouble());
        }
    }
    if(pJson.isMember("id"))
    {
        dirtyFlag_[2]=true;
        if(!pJson["id"].isNull())
        {
            id_=std::make_shared<uint64_t>((uint64_t)pJson["id"].asUInt64());
        }
    }
}

void Config::updateByMasqueradedJson(const Json::Value &pJson,
                                            const std::vector<std::string> &pMasqueradingVector) noexcept(false)
{
    if(pMasqueradingVector.size() != 3)
    {
        LOG_ERROR << "Bad masquerading vector";
        return;
    }
    if(!pMasqueradingVector[0].empty() && pJson.isMember(pMasqueradingVector[0]))
    {
        dirtyFlag_[0] = true;
        if(!pJson[pMasqueradingVector[0]].isNull())
        {
            limittemp_=std::make_shared<double>(pJson[pMasqueradingVector[0]].asDouble());
        }
    }
    if(!pMasqueradingVector[1].empty() && pJson.isMember(pMasqueradingVector[1]))
    {
        dirtyFlag_[1] = true;
        if(!pJson[pMasqueradingVector[1]].isNull())
        {
            hysteresis_=std::make_shared<double>(pJson[pMasqueradingVector[1]].asDouble());
        }
    }
    if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
    {
        if(!pJson[pMasqueradingVector[2]].isNull())
        {
            id_=std::make_shared<uint64_t>((uint64_t)pJson[pMasqueradingVector[2]].asUInt64());
        }
    }
}
                                                                    
void Config::updateByJson(const Json::Value &pJson) noexcept(false)
{
    if(pJson.isMember("limitTemp"))
    {
        dirtyFlag_[0] = true;
        if(!pJson["limitTemp"].isNull())
        {
            limittemp_=std::make_shared<double>(pJson["limitTemp"].asDouble());
        }
    }
    if(pJson.isMember("hysteresis"))
    {
        dirtyFlag_[1] = true;
        if(!pJson["hysteresis"].isNull())
        {
            hysteresis_=std::make_shared<double>(pJson["hysteresis"].asDouble());
        }
    }
    if(pJson.isMember("id"))
    {
        if(!pJson["id"].isNull())
        {
            id_=std::make_shared<uint64_t>((uint64_t)pJson["id"].asUInt64());
        }
    }
}

const double &Config::getValueOfLimittemp() const noexcept
{
    const static double defaultValue = double();
    if(limittemp_)
        return *limittemp_;
    return defaultValue;
}
const std::shared_ptr<double> &Config::getLimittemp() const noexcept
{
    return limittemp_;
}
void Config::setLimittemp(const double &pLimittemp) noexcept
{
    limittemp_ = std::make_shared<double>(pLimittemp);
    dirtyFlag_[0] = true;
}




const double &Config::getValueOfHysteresis() const noexcept
{
    const static double defaultValue = double();
    if(hysteresis_)
        return *hysteresis_;
    return defaultValue;
}
const std::shared_ptr<double> &Config::getHysteresis() const noexcept
{
    return hysteresis_;
}
void Config::setHysteresis(const double &pHysteresis) noexcept
{
    hysteresis_ = std::make_shared<double>(pHysteresis);
    dirtyFlag_[1] = true;
}




const uint64_t &Config::getValueOfId() const noexcept
{
    const static uint64_t defaultValue = uint64_t();
    if(id_)
        return *id_;
    return defaultValue;
}
const std::shared_ptr<uint64_t> &Config::getId() const noexcept
{
    return id_;
}
void Config::setId(const uint64_t &pId) noexcept
{
    id_ = std::make_shared<uint64_t>(pId);
    dirtyFlag_[2] = true;
}



const typename Config::PrimaryKeyType & Config::getPrimaryKey() const
{
    assert(id_);
    return *id_;
}

void Config::updateId(const uint64_t id)
{
}

const std::vector<std::string> &Config::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
        "limitTemp",
        "hysteresis",
        "id"
    };
    return inCols;
}

void Config::outputArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(dirtyFlag_[0])
    {
        if(getLimittemp())
        {
            binder << getValueOfLimittemp();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[1])
    {
        if(getHysteresis())
        {
            binder << getValueOfHysteresis();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getId())
        {
            binder << getValueOfId();
        }
        else
        {
            binder << nullptr;
        }
    }
}

const std::vector<std::string> Config::updateColumns() const
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
    return ret;
}

void Config::updateArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(dirtyFlag_[0])
    {
        if(getLimittemp())
        {
            binder << getValueOfLimittemp();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[1])
    {
        if(getHysteresis())
        {
            binder << getValueOfHysteresis();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(dirtyFlag_[2])
    {
        if(getId())
        {
            binder << getValueOfId();
        }
        else
        {
            binder << nullptr;
        }
    }
}
Json::Value Config::toJson() const
{
    Json::Value ret;
    if(getLimittemp())
    {
        ret["limitTemp"]=getValueOfLimittemp();
    }
    else
    {
        ret["limitTemp"]=Json::Value();
    }
    if(getHysteresis())
    {
        ret["hysteresis"]=getValueOfHysteresis();
    }
    else
    {
        ret["hysteresis"]=Json::Value();
    }
    if(getId())
    {
        ret["id"]=(Json::UInt64)getValueOfId();
    }
    else
    {
        ret["id"]=Json::Value();
    }
    return ret;
}

Json::Value Config::toMasqueradedJson(
    const std::vector<std::string> &pMasqueradingVector) const
{
    Json::Value ret;
    if(pMasqueradingVector.size() == 3)
    {
        if(!pMasqueradingVector[0].empty())
        {
            if(getLimittemp())
            {
                ret[pMasqueradingVector[0]]=getValueOfLimittemp();
            }
            else
            {
                ret[pMasqueradingVector[0]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[1].empty())
        {
            if(getHysteresis())
            {
                ret[pMasqueradingVector[1]]=getValueOfHysteresis();
            }
            else
            {
                ret[pMasqueradingVector[1]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[2].empty())
        {
            if(getId())
            {
                ret[pMasqueradingVector[2]]=(Json::UInt64)getValueOfId();
            }
            else
            {
                ret[pMasqueradingVector[2]]=Json::Value();
            }
        }
        return ret;
    }
    LOG_ERROR << "Masquerade failed";
    if(getLimittemp())
    {
        ret["limitTemp"]=getValueOfLimittemp();
    }
    else
    {
        ret["limitTemp"]=Json::Value();
    }
    if(getHysteresis())
    {
        ret["hysteresis"]=getValueOfHysteresis();
    }
    else
    {
        ret["hysteresis"]=Json::Value();
    }
    if(getId())
    {
        ret["id"]=(Json::UInt64)getValueOfId();
    }
    else
    {
        ret["id"]=Json::Value();
    }
    return ret;
}

bool Config::validateJsonForCreation(const Json::Value &pJson, std::string &err)
{
    if(pJson.isMember("limitTemp"))
    {
        if(!validJsonOfField(0, "limitTemp", pJson["limitTemp"], err, true))
            return false;
    }
    if(pJson.isMember("hysteresis"))
    {
        if(!validJsonOfField(1, "hysteresis", pJson["hysteresis"], err, true))
            return false;
    }
    if(pJson.isMember("id"))
    {
        if(!validJsonOfField(2, "id", pJson["id"], err, true))
            return false;
    }
    else
    {
        err="The id column cannot be null";
        return false;
    }
    return true;
}
bool Config::validateMasqueradedJsonForCreation(const Json::Value &pJson,
                                                const std::vector<std::string> &pMasqueradingVector,
                                                std::string &err)
{
    if(pMasqueradingVector.size() != 3)
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
        else
        {
            err="The " + pMasqueradingVector[2] + " column cannot be null";
            return false;
        }
    }
    return true;
}
bool Config::validateJsonForUpdate(const Json::Value &pJson, std::string &err)
{
    if(pJson.isMember("limitTemp"))
    {
        if(!validJsonOfField(0, "limitTemp", pJson["limitTemp"], err, false))
            return false;
    }
    if(pJson.isMember("hysteresis"))
    {
        if(!validJsonOfField(1, "hysteresis", pJson["hysteresis"], err, false))
            return false;
    }
    if(pJson.isMember("id"))
    {
        if(!validJsonOfField(2, "id", pJson["id"], err, false))
            return false;
    }
    else
    {
        err = "The value of primary key must be set in the json object for update";
        return false;
    }
    return true;
}
bool Config::validateMasqueradedJsonForUpdate(const Json::Value &pJson,
                                              const std::vector<std::string> &pMasqueradingVector,
                                              std::string &err)
{
    if(pMasqueradingVector.size() != 3)
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
    else
    {
        err = "The value of primary key must be set in the json object for update";
        return false;
    }
    return true;
}
bool Config::validJsonOfField(size_t index,
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
            if(!pJson.isUInt64())
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