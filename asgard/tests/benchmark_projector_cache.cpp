#include "asgard/mode_costing.h"
#include "asgard/projector.h"

#include "utils/timer.h"

#include <valhalla/baldr/graphreader.h>
#include <valhalla/midgard/pointll.h>

#include <boost/program_options.hpp>
#include <boost/progress.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/range/algorithm/transform.hpp>

#include <algorithm>
#include <random>
#include <thread>

namespace po = boost::program_options;
using namespace valhalla::baldr;
using namespace asgard;
using ListOfLocations = std::vector<std::vector<valhalla::midgard::PointLL>>;
using ListOfResults = std::vector<std::unordered_map<valhalla::midgard::PointLL, PathLocation>>;

void compute(const Projector& projector, boost::property_tree::ptree conf, boost::progress_display& show_progress, ListOfLocations list_of_locations) {

    for (auto& locations : list_of_locations) {
        std::random_shuffle(locations.begin(), locations.end());
    }
    valhalla::baldr::GraphReader graph(conf.get_child("mjolnir"));
    ModeCosting mode_costing;
    auto costing = mode_costing.get_costing_for_mode("car");
    ListOfResults list_of_results;
    for (auto locations : list_of_locations) {
        ++show_progress;
        auto result = projector(begin(locations), end(locations), graph, "car", costing);

        std::this_thread::yield();
        //store the pointer to prevent any kind of optimisation from the compiler
        // DO NOT USE THIS POINTER!!! it will have been freed
        list_of_results.push_back(result);
    }
    std::cout << "Number of results: " << list_of_results.size() << std::endl;
}

ListOfLocations build_list_of_locations(size_t nb_threads) {
    size_t list_size = 1000 / nb_threads;
    ListOfLocations list_of_locations;
    std::vector<std::string> locations = {"coord:2.417036:48.858501",
                                          "coord:2.417822:48.838296",
                                          "coord:2.411921:48.853166",
                                          "coord:2.452793:48.853645",
                                          "coord:2.411743:48.852995",
                                          "coord:2.443901:48.860825",
                                          "coord:2.410836:48.847019",
                                          "coord:2.436985:48.86271",
                                          "coord:2.417617:48.838144",
                                          "coord:2.411935:48.853624",
                                          "coord:2.441424:48.861825",
                                          "coord:2.420009:48.860629",
                                          "coord:2.441165:48.861978",
                                          "coord:2.436522:48.863007",
                                          "coord:2.45462:48.848511",
                                          "coord:2.41036:48.847199",
                                          "coord:2.441315:48.862104",
                                          "coord:2.41025:48.84701",
                                          "coord:2.453311:48.85395",
                                          "coord:2.411458:48.853759",
                                          "coord:2.410982:48.844305",
                                          "coord:2.410831:48.853184",
                                          "coord:2.410832:48.844125",
                                          "coord:2.441847:48.862283",
                                          "coord:2.410558:48.852906",
                                          "coord:2.414761:48.858179",
                                          "coord:2.409706:48.847226",
                                          "coord:2.421208:48.835562",
                                          "coord:2.409692:48.846867",
                                          "coord:2.410531:48.853184",
                                          "coord:2.409488:48.847298",
                                          "coord:2.410477:48.853382",
                                          "coord:2.409515:48.846813",
                                          "coord:2.442501:48.862426",
                                          "coord:2.41151:48.842111",
                                          "coord:2.410696:48.853993",
                                          "coord:2.414584:48.858494",
                                          "coord:2.440976:48.862949",
                                          "coord:2.455725:48.849355",
                                          "coord:2.441262:48.862895",
                                          "coord:2.455713:48.849993",
                                          "coord:2.430026:48.864037",
                                          "coord:2.412039:48.841032",
                                          "coord:2.410218:48.843622",
                                          "coord:2.410082:48.853517",
                                          "coord:2.409946:48.853293",
                                          "coord:2.441562:48.863047",
                                          "coord:2.429795:48.864199",
                                          "coord:2.420309:48.835248",
                                          "coord:2.420526:48.835095",
                                          "coord:2.409891:48.843532",
                                          "coord:2.447701:48.860822",
                                          "coord:2.447756:48.860912",
                                          "coord:2.411517:48.856761",
                                          "coord:2.449851:48.859813",
                                          "coord:2.456467:48.846335",
                                          "coord:2.419532:48.835132",
                                          "coord:2.444174:48.834627",
                                          "coord:2.456734:48.850028",
                                          "coord:2.444014:48.862803",
                                          "coord:2.449756:48.859984",
                                          "coord:2.444241:48.83442",
                                          "coord:2.420239:48.834547",
                                          "coord:2.411573:48.857381",
                                          "coord:2.457278:48.849354",
                                          "coord:2.41655:48.861269",
                                          "coord:2.456876:48.852482",
                                          "coord:2.416891:48.861754",
                                          "coord:2.438392:48.864857",
                                          "coord:2.417055:48.861898",
                                          "coord:2.409118:48.855531",
                                          "coord:2.437684:48.865163",
                                          "coord:2.432209:48.865527",
                                          "coord:2.432005:48.86559",
                                          "coord:2.457924:48.84618",
                                          "coord:2.406697:48.847525",
                                          "coord:2.457206:48.853614",
                                          "coord:2.406642:48.847309",
                                          "coord:2.40652:48.84792",
                                          "coord:2.416088:48.861944",
                                          "coord:2.456433:48.855259",
                                          "coord:2.415952:48.862016",
                                          "coord:2.406262:48.847956",
                                          "coord:2.406457:48.851174",
                                          "coord:2.406292:48.850275",
                                          "coord:2.409247:48.840567",
                                          "coord:2.426079:48.865621",
                                          "coord:2.42785:48.865989",
                                          "coord:2.406404:48.852603",
                                          "coord:2.42627:48.865783",
                                          "coord:2.428014:48.866096",
                                          "coord:2.458444:48.853163",
                                          "coord:2.406077:48.852208",
                                          "coord:2.416985:48.83419",
                                          "coord:2.442997:48.864969",
                                          "coord:2.459174:48.850709",
                                          "coord:2.409056:48.839893",
                                          "coord:2.448857:48.834631",
                                          "coord:2.408784:48.840064",
                                          "coord:2.415735:48.86269",
                                          "coord:2.405944:48.844919",
                                          "coord:2.406026:48.844541",
                                          "coord:2.406132:48.853142",
                                          "coord:2.449279:48.834622",
                                          "coord:2.408729:48.839902",
                                          "coord:2.415653:48.862915",
                                          "coord:2.409831:48.858847",
                                          "coord:2.4056:48.852495",
                                          "coord:2.45819:48.855105",
                                          "coord:2.43244:48.84868",
                                          "coord:2.27726:48.81071",
                                          "coord:2.276444:48.811409",
                                          "coord:2.280866:48.811519",
                                          "coord:2.280566:48.812094",
                                          "coord:2.277686:48.808021",
                                          "coord:2.274433:48.808352",
                                          "coord:2.282038:48.810306",
                                          "coord:2.27723:48.813935",
                                          "coord:2.273516:48.812827",
                                          "coord:2.272577:48.812539",
                                          "coord:2.27205:48.809501",
                                          "coord:2.27791:48.814483",
                                          "coord:2.278903:48.814376",
                                          "coord:2.282923:48.809731",
                                          "coord:2.279638:48.81434",
                                          "coord:2.27449:48.814239",
                                          "coord:2.273066:48.813888",
                                          "coord:2.276956:48.8154",
                                          "coord:2.272031:48.813914",
                                          "coord:2.272765:48.814544",
                                          "coord:2.2848:48.810532",
                                          "coord:2.285235:48.810865",
                                          "coord:2.271786:48.814543",
                                          "coord:2.285289:48.810946",
                                          "coord:2.285412:48.810793",
                                          "coord:2.269097:48.809778",
                                          "coord:2.282986:48.814953",
                                          "coord:2.282917:48.815106",
                                          "coord:2.280099:48.816273",
                                          "coord:2.269392:48.813553",
                                          "coord:2.280072:48.816327",
                                          "coord:2.273389:48.805251",
                                          "coord:2.285388:48.807575",
                                          "coord:2.274614:48.816729",
                                          "coord:2.285714:48.807809",
                                          "coord:2.280275:48.816669",
                                          "coord:2.275729:48.816972",
                                          "coord:2.274831:48.816864",
                                          "coord:2.275498:48.81699",
                                          "coord:2.275457:48.817062",
                                          "coord:2.269537:48.806246",
                                          "coord:2.274996:48.804029",
                                          "coord:2.277199:48.817575",
                                          "coord:2.286511:48.813876",
                                          "coord:2.281758:48.817029",
                                          "coord:2.266605:48.811197",
                                          "coord:2.286933:48.813777",
                                          "coord:2.266263:48.812608",
                                          "coord:2.286329:48.805976",
                                          "coord:2.267428:48.806586",
                                          "coord:2.287804:48.81411",
                                          "coord:2.288504:48.808098",
                                          "coord:2.288653:48.808287",
                                          "coord:2.286737:48.805877",
                                          "coord:2.283282:48.817757",
                                          "coord:2.271917:48.818561",
                                          "coord:2.284384:48.817965",
                                          "coord:2.266816:48.815951",
                                          "coord:2.284452:48.818046",
                                          "coord:2.274216:48.819326",
                                          "coord:2.263869:48.811537",
                                          "coord:2.274502:48.819425",
                                          "coord:2.265225:48.815061",
                                          "coord:2.280517:48.8195",
                                          "coord:2.29068:48.808737",
                                          "coord:2.279455:48.819805",
                                          "coord:2.265062:48.815339",
                                          "coord:2.279183:48.819904",
                                          "coord:2.271161:48.802301",
                                          "coord:2.26861:48.818199",
                                          "coord:2.291306:48.808836",
                                          "coord:2.262984:48.811743",
                                          "coord:2.272223:48.801835",
                                          "coord:2.278619:48.801209",
                                          "coord:2.267118:48.80389",
                                          "coord:2.288031:48.804314",
                                          "coord:2.288262:48.804431",
                                          "coord:2.278578:48.801065",
                                          "coord:2.271856:48.801646",
                                          "coord:2.291783:48.808782",
                                          "coord:2.266057:48.804285",
                                          "coord:2.288725:48.804242",
                                          "coord:2.288847:48.804296",
                                          "coord:2.288793:48.804242",
                                          "coord:2.290742:48.815442",
                                          "coord:2.286629:48.818685",
                                          "coord:2.289133:48.804098",
                                          "coord:2.2881:48.818065",
                                          "coord:2.284347:48.801418",
                                          "coord:2.283286:48.801094",
                                          "coord:2.264977:48.817262",
                                          "coord:2.282639:48.820543",
                                          "coord:2.292926:48.80881",
                                          "coord:2.291055:48.816035",
                                          "coord:2.292881:48.813106",
                                          "coord:2.277603:48.821278",
                                          "coord:2.273315:48.821195",
                                          "coord:2.287366:48.802111",
                                          "coord:2.28247:48.800348",
                                          "coord:2.283178:48.80042",
                                          "coord:2.265003:48.818206",
                                          "coord:2.28753:48.801914",
                                          "coord:2.282715:48.800168",
                                          "coord:2.267206:48.81969",
                                          "coord:2.293213:48.806913",
                                          "coord:2.267111:48.819672",
                                          "coord:2.267179:48.819852",
                                          "coord:2.276676:48.822023",
                                          "coord:2.280705:48.821819",
                                          "coord:2.294365:48.812028",
                                          "coord:2.29442:48.811848",
                                          "coord:2.271192:48.821364",
                                          "coord:2.284293:48.800304",
                                          "coord:2.271287:48.8214",
                                          "coord:2.273342:48.821896",
                                          "coord:2.285252:48.820922",
                                          "coord:2.271205:48.821508",
                                          "coord:2.264793:48.802603",
                                          "coord:2.266005:48.801831",
                                          "coord:2.294165:48.80739",
                                          "coord:2.285824:48.82094",
                                          "coord:2.266183:48.801561",
                                          "coord:2.272987:48.822093",
                                          "coord:2.279616:48.822348",
                                          "coord:2.286015:48.820958",
                                          "coord:2.294356:48.807246",
                                          "coord:2.293505:48.815766",
                                          "coord:2.26538:48.801552",
                                          "coord:2.26862:48.800071",
                                          "coord:2.271342:48.799237",
                                          "coord:2.276185:48.82285",
                                          "coord:2.263695:48.818969",
                                          "coord:2.29142:48.818525",
                                          "coord:2.29142:48.818525",
                                          "coord:2.26538:48.801309",
                                          "coord:2.291556:48.818525",
                                          "coord:2.263954:48.819266",
                                          "coord:2.282106:48.822583",
                                          "coord:2.258715:48.809277",
                                          "coord:2.271258:48.822407",
                                          "coord:2.262534:48.803069",
                                          "coord:2.273667:48.82284",
                                          "coord:2.261167:48.817089",
                                          "coord:2.275166:48.798412",
                                          "coord:2.27609:48.823084",
                                          "coord:2.292062:48.818388",
                                          "coord:2.282392:48.822664",
                                          "coord:2.258345:48.811353",
                                          "coord:2.25852:48.812612",
                                          "coord:2.262303:48.803015",
                                          "coord:2.26099:48.817251",
                                          "coord:2.291924:48.818741",
                                          "coord:2.258182:48.810832",
                                          "coord:2.284802:48.822252",
                                          "coord:2.258649:48.807875",
                                          "coord:2.268934:48.799361",
                                          "coord:2.258342:48.812701",
                                          "coord:2.284023:48.798892",
                                          "coord:2.288301:48.821085",
                                          "coord:2.296449:48.809566",
                                          "coord:2.273748:48.82319",
                                          "coord:2.28502:48.822351",
                                          "coord:2.284404:48.798875",
                                          "coord:2.295874:48.814194",
                                          "coord:2.296518:48.809395",
                                          "coord:2.267693:48.821866",
                                          "coord:2.263014:48.819454",
                                          "coord:2.289118:48.82096",
                                          "coord:2.286634:48.799379",
                                          "coord:2.28643:48.79928",
                                          "coord:2.260771:48.817727",
                                          "coord:2.259715:48.804874",
                                          "coord:2.289172:48.821013",
                                          "coord:2.258965:48.805952",
                                          "coord:2.294456:48.817016",
                                          "coord:2.273068:48.823388",
                                          "coord:2.294865:48.816755",
                                          "coord:2.257379:48.810858",
                                          "coord:2.25932:48.805017",
                                          "coord:2.267774:48.822261",
                                          "coord:2.291187:48.820115",
                                          "coord:2.292781:48.819226",
                                          "coord:2.258571:48.805547",
                                          "coord:2.291459:48.820322",
                                          "coord:2.263339:48.820524",
                                          "coord:2.257768:48.814741",
                                          "coord:2.281847:48.797597",
                                          "coord:2.266376:48.799306",
                                          "coord:2.25707:48.80844",
                                          "coord:2.296676:48.815012",
                                          "coord:2.273598:48.823999",
                                          "coord:2.270051:48.798049",
                                          "coord:2.257564:48.814651",
                                          "coord:2.297126:48.814285",
                                          "coord:2.26425:48.821235",
                                          "coord:2.266984:48.822494",
                                          "coord:2.291105:48.820834",
                                          "coord:2.281943:48.797435",
                                          "coord:2.291554:48.820646",
                                          "coord:2.268073:48.822998",
                                          "coord:2.29105:48.821077",
                                          "coord:2.295327:48.817672",
                                          "coord:2.297303:48.814707",
                                          "coord:2.291064:48.82114",
                                          "coord:2.273584:48.82435",
                                          "coord:2.267942:48.798255",
                                          "coord:2.282431:48.824192",
                                          "coord:2.298233:48.808829",
                                          "coord:2.272726:48.824331",
                                          "coord:2.263586:48.80005",
                                          "coord:2.297479:48.814923",
                                          "coord:2.298491:48.809279",
                                          "coord:2.264467:48.821963",
                                          "coord:2.265247:48.799062",
                                          "coord:2.291069:48.799947",
                                          "coord:2.274243:48.796712",
                                          "coord:2.298721:48.811184",
                                          "coord:2.282418:48.824444",
                                          "coord:2.274931:48.824782",
                                          "coord:2.272576:48.824529",
                                          "coord:2.267439:48.798075",
                                          "coord:2.291015:48.799749",
                                          "coord:2.273991:48.824772",
                                          "coord:2.287397:48.79813",
                                          "coord:2.267024:48.823285",
                                          "coord:2.286826:48.797896",
                                          "coord:2.256529:48.806283",
                                          "coord:2.297976:48.806232",
                                          "coord:2.289797:48.822524",
                                          "coord:2.273773:48.824961",
                                          "coord:2.287615:48.797959",
                                          "coord:2.298289:48.806493",
                                          "coord:2.263056:48.799654",
                                          "coord:2.255436:48.808844",
                                          "coord:2.261722:48.80039",
                                          "coord:2.287874:48.79795",
                                          "coord:2.263002:48.799582",
                                          "coord:2.294143:48.801296",
                                          "coord:2.273678:48.825123",
                                          "coord:2.260905:48.800749",
                                          "coord:2.259761:48.801557",
                                          "coord:2.287904:48.823664",
                                          "coord:2.288367:48.82353",
                                          "coord:2.273542:48.825266",
                                          "coord:2.258592:48.818912",
                                          "coord:2.259788:48.801378",
                                          "coord:2.299782:48.811221",
                                          "coord:2.299768:48.811796",
                                          "coord:2.27346:48.825365",
                                          "coord:2.299836:48.811266",
                                          "coord:2.258591:48.819092",
                                          "coord:2.273133:48.825347",
                                          "coord:2.299823:48.811688",
                                          "coord:2.299877:48.811302",
                                          "coord:2.257459:48.803371",
                                          "coord:2.295408:48.801665",
                                          "coord:2.27585:48.795725",
                                          "coord:2.257486:48.803201",
                                          "coord:2.300027:48.81185",
                                          "coord:2.300109:48.811149",
                                          "coord:2.259339:48.820063",
                                          "coord:2.259339:48.820063",
                                          "coord:2.297488:48.803688",
                                          "coord:2.296238:48.819147",
                                          "coord:2.260797:48.800228",
                                          "coord:2.273364:48.825581",
                                          "coord:2.257309:48.803273",
                                          "coord:2.272684:48.825509",
                                          "coord:2.25876:48.819674",
                                          "coord:2.259773:48.820603",
                                          "coord:2.300313:48.811284",
                                          "coord:2.297855:48.803841",
                                          "coord:2.296265:48.819353",
                                          "coord:2.300354:48.811356",
                                          "coord:2.285141:48.796385",
                                          "coord:2.256873:48.803488",
                                          "coord:2.300436:48.810601",
                                          "coord:2.277692:48.82605",
                                          "coord:2.275469:48.795383",
                                          "coord:2.285345:48.796277",
                                          "coord:2.256765:48.80329",
                                          "coord:2.25671:48.803344",
                                          "coord:2.272639:48.795507",
                                          "coord:2.272299:48.795534",
                                          "coord:2.258875:48.820485",
                                          "coord:2.25575:48.817274",
                                          "coord:2.267008:48.824957",
                                          "coord:2.25397:48.807018",
                                          "coord:2.294017:48.822058",
                                          "coord:2.301307:48.810286",
                                          "coord:2.264246:48.824084",
                                          "coord:2.253122:48.809687",
                                          "coord:2.253766:48.80691",
                                          "coord:2.280544:48.794873",
                                          "coord:2.253013:48.809786",
                                          "coord:2.295763:48.800308",
                                          "coord:2.26992:48.825992",
                                          "coord:2.262763:48.823606",
                                          "coord:2.296157:48.800578",
                                          "coord:2.254811:48.817202",
                                          "coord:2.300187:48.816452",
                                          "coord:2.278985:48.826833",
                                          "coord:2.292764:48.823307",
                                          "coord:2.292586:48.823441",
                                          "coord:2.272817:48.794725",
                                          "coord:2.301672:48.813252",
                                          "coord:2.273117:48.794654",
                                          "coord:2.300949:48.815445",
                                          "coord:2.256739:48.819864",
                                          "coord:2.278671:48.827013",
                                          "coord:2.252357:48.811313",
                                          "coord:2.273049:48.794528",
                                          "coord:2.256168:48.819531",
                                          "coord:2.294009:48.798483",
                                          "coord:2.272001:48.794545",
                                          "coord:2.279025:48.82721",
                                          "coord:2.278644:48.827372",
                                          "coord:2.272954:48.794258",
                                          "coord:2.252349:48.807547",
                                          "coord:2.272927:48.79424",
                                          "coord:2.293765:48.797971",
                                          "coord:2.288637:48.825705",
                                          "coord:2.273689:48.827388",
                                          "coord:2.299245:48.819327",
                                          "coord:2.271497:48.827189",
                                          "coord:2.272804:48.794051",
                                          "coord:2.259022:48.822633",
                                          "coord:2.294146:48.797953",
                                          "coord:2.266109:48.825981",
                                          "coord:2.27328:48.827504",
                                          "coord:2.258926:48.822741",
                                          "coord:2.268913:48.794552",
                                          "coord:2.302665:48.814116",
                                          "coord:2.254644:48.819062",
                                          "coord:2.273036:48.793854",
                                          "coord:2.251429:48.812553",
                                          "coord:2.274369:48.827747",
                                          "coord:2.27305:48.793782",
                                          "coord:2.271484:48.827449",
                                          "coord:2.251615:48.807592",
                                          "coord:2.302897:48.813873",
                                          "coord:2.273131:48.793719",
                                          "coord:2.291891:48.824978",
                                          "coord:2.283313:48.827473",
                                          "coord:2.283837:48.793994",
                                          "coord:2.261279:48.824405",
                                          "coord:2.268668:48.794382",
                                          "coord:2.287877:48.794903",
                                          "coord:2.272681:48.827791",
                                          "coord:2.26121:48.824495",
                                          "coord:2.300348:48.81913",
                                          "coord:2.28462:48.82742",
                                          "coord:2.295397:48.798016",
                                          "coord:2.29231:48.796325",
                                          "coord:2.277757:48.793236",
                                          "coord:2.303742:48.811914",
                                          "coord:2.284545:48.793841",
                                          "coord:2.272218:48.828016",
                                          "coord:2.281052:48.828155",
                                          "coord:2.292569:48.796244",
                                          "coord:2.288938:48.794823",
                                          "coord:2.283946:48.793607",
                                          "coord:2.253393:48.818828",
                                          "coord:2.274994:48.828377",
                                          "coord:2.301873:48.817908",
                                          "coord:2.30415:48.811941",
                                          "coord:2.260597:48.82472",
                                          "coord:2.272316:48.79317",
                                          "coord:2.280369:48.792941",
                                          "coord:2.292326:48.825607",
                                          "coord:2.260475:48.824791",
                                          "coord:2.293034:48.825293",
                                          "coord:2.266369:48.794272",
                                          "coord:2.293075:48.82532",
                                          "coord:2.29795:48.822446",
                                          "coord:2.273361:48.828511",
                                          "coord:2.280723:48.79286",
                                          "coord:2.268121:48.827708",
                                          "coord:2.292557:48.825697",
                                          "coord:2.284232:48.793203",
                                          "coord:2.304749:48.811078"};

    std::vector<valhalla::midgard::PointLL> pointLLs;
    boost::transform(locations, std::back_inserter(pointLLs), [](const auto& coord) {
        return valhalla::midgard::PointLL{navitia::parse_coordinate(coord)};
    });

    for (size_t i = 0; i < list_size; ++i) {
        list_of_locations.push_back(pointLLs);
    }

    std::cout << "nb of locations = " << (list_of_locations.size() * locations.size()) * nb_threads << std::endl;
    return list_of_locations;
}

int main(int argc, char** argv) {
    po::options_description desc("Options de l'outil de benchmark");
    size_t cache_size = 0;
    size_t nb_threads = 0;
    std::string conf_path = "";

    // clang-format off
    desc.add_options()
            ("help", "Show this message")
            ("size,s", po::value<size_t>(&cache_size)->default_value(10), "cache size")
            ("threads,t", po::value<size_t>(&nb_threads)->default_value(3), "number of threads to run")
            ("conf_path,c", po::value<std::string>(&conf_path)->default_value(""), "conf_path");
    // clang-format on

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    auto l = build_list_of_locations(nb_threads);
    std::cout << "cache_size = " << cache_size << std::endl;
    std::cout << "nb_threads = " << nb_threads << std::endl;
    std::cout << "conf_path = " << conf_path << std::endl;

    boost::property_tree::ptree conf;
    boost::property_tree::read_json(conf_path, conf);
    Projector p(cache_size);
    boost::progress_display show_progress(l.size() * nb_threads);
    {
        Timer t("Projector cache ");
        std::vector<std::thread> threads;

        for (size_t i = 0; i < nb_threads; ++i) {
            auto t = std::thread(compute, std::ref(p), conf, std::ref(show_progress), l);
            threads.push_back(std::move(t));
        }
        for (auto& th : threads) {
            th.join();
        }
    }

    std::cout << "Number of requests: " << l.size() << std::endl;
}
