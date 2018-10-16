/**
* OpenAPI Petstore
* This is a sample server Petstore server. For this sample, you can use the api key `special-key` to test the authorization filters.
*
* OpenAPI spec version: 1.0.0
* 
*
* NOTE: This class is auto generated by OpenAPI Generator (https://openapi-generator.tech).
* https://openapi-generator.tech
* Do not edit the class manually.
*/

#include "PetApi.h"
#include "Helpers.h"

namespace org {
namespace openapitools {
namespace server {
namespace api {

using namespace org::openapitools::server::helpers;
using namespace org::openapitools::server::model;

PetApi::PetApi(Pistache::Address addr)
    : httpEndpoint(addr)
{ };

void PetApi::init(size_t thr = 2) {
    auto opts = Pistache::Http::Endpoint::options()
        .threads(thr)
        .flags(Pistache::Tcp::Options::InstallSignalHandler);
    httpEndpoint.init(opts);
    setupRoutes();
}

void PetApi::start() {
    httpEndpoint.setHandler(router.handler());
    httpEndpoint.serve();
}

void PetApi::shutdown() {
    httpEndpoint.shutdown();
}

void PetApi::setupRoutes() {
    using namespace Pistache::Rest;

    Routes::Post(router, base + "/pet", Routes::bind(&PetApi::add_pet_handler, this));
    Routes::Delete(router, base + "/pet/:petId", Routes::bind(&PetApi::delete_pet_handler, this));
    Routes::Get(router, base + "/pet/findByStatus", Routes::bind(&PetApi::find_pets_by_status_handler, this));
    Routes::Get(router, base + "/pet/findByTags", Routes::bind(&PetApi::find_pets_by_tags_handler, this));
    Routes::Get(router, base + "/pet/:petId", Routes::bind(&PetApi::get_pet_by_id_handler, this));
    Routes::Put(router, base + "/pet", Routes::bind(&PetApi::update_pet_handler, this));
    Routes::Post(router, base + "/pet/:petId", Routes::bind(&PetApi::update_pet_with_form_handler, this));
    Routes::Post(router, base + "/pet/:petId/uploadImage", Routes::bind(&PetApi::upload_file_handler, this));

    // Default handler, called when a route is not found
    router.addCustomHandler(Routes::bind(&PetApi::pet_api_default_handler, this));
}

void PetApi::add_pet_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {

    // Getting the body param
    
    Pet pet;
    
    try {
      nlohmann::json request_body = nlohmann::json::parse(request.body());
    
      pet.fromJson(request_body);
    
      this->add_pet(pet, response);
    } catch (std::runtime_error & e) {
      //send a 400 error
      response.send(Pistache::Http::Code::Bad_Request, e.what());
      return;
    }

}
void PetApi::delete_pet_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {
    // Getting the path params
    auto petId = request.param(":petId").as<int64_t>();
    
    // Getting the header params
    auto apiKey = request.headers().tryGetRaw("api_key");

    try {
      this->delete_pet(petId, apiKey, response);
    } catch (std::runtime_error & e) {
      //send a 400 error
      response.send(Pistache::Http::Code::Bad_Request, e.what());
      return;
    }

}
void PetApi::find_pets_by_status_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {

    // Getting the query params
    auto statusQuery = request.query().get("status");
    Pistache::Optional<std::vector<std::string>> status;
    if(!statusQuery.isEmpty()){
        std::vector<std::string> value;
        if(fromStringValue(statusQuery.get(), value)){
            status = Pistache::Some(value);
        }
    }
    
    try {
      this->find_pets_by_status(status, response);
    } catch (std::runtime_error & e) {
      //send a 400 error
      response.send(Pistache::Http::Code::Bad_Request, e.what());
      return;
    }

}
void PetApi::find_pets_by_tags_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {

    // Getting the query params
    auto tagsQuery = request.query().get("tags");
    Pistache::Optional<std::vector<std::string>> tags;
    if(!tagsQuery.isEmpty()){
        std::vector<std::string> value;
        if(fromStringValue(tagsQuery.get(), value)){
            tags = Pistache::Some(value);
        }
    }
    
    try {
      this->find_pets_by_tags(tags, response);
    } catch (std::runtime_error & e) {
      //send a 400 error
      response.send(Pistache::Http::Code::Bad_Request, e.what());
      return;
    }

}
void PetApi::get_pet_by_id_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {
    // Getting the path params
    auto petId = request.param(":petId").as<int64_t>();
    
    try {
      this->get_pet_by_id(petId, response);
    } catch (std::runtime_error & e) {
      //send a 400 error
      response.send(Pistache::Http::Code::Bad_Request, e.what());
      return;
    }

}
void PetApi::update_pet_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {

    // Getting the body param
    
    Pet pet;
    
    try {
      nlohmann::json request_body = nlohmann::json::parse(request.body());
    
      pet.fromJson(request_body);
    
      this->update_pet(pet, response);
    } catch (std::runtime_error & e) {
      //send a 400 error
      response.send(Pistache::Http::Code::Bad_Request, e.what());
      return;
    }

}
void PetApi::update_pet_with_form_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {
    try {
      this->update_pet_with_form(request, response);
    } catch (std::runtime_error & e) {
      //send a 400 error
      response.send(Pistache::Http::Code::Bad_Request, e.what());
      return;
    }

}
void PetApi::upload_file_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {
    try {
      this->upload_file(request, response);
    } catch (std::runtime_error & e) {
      //send a 400 error
      response.send(Pistache::Http::Code::Bad_Request, e.what());
      return;
    }

}

void PetApi::pet_api_default_handler(const Pistache::Rest::Request &request, Pistache::Http::ResponseWriter response) {
    response.send(Pistache::Http::Code::Not_Found, "The requested method does not exist");
}

}
}
}
}
