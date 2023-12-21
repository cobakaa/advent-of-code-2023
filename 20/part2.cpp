#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

enum Signal { HIGH, LOW, NONE };

enum Type { FLIPFLOP, CONJUNCTION, SENDER };

struct Module {
    std::string name;
    Signal signal = NONE;
    Type type;
    bool on = false;
    std::unordered_map<std::string, Signal> last = {};
};

template <> struct std::hash<Module> {
    size_t operator()(const Module &m) const {
        return std::hash<std::string>()(m.name);
    }
};

bool operator==(const Module &m1, const Module &m2) {
    return m1.name == m2.name;
}

int64_t GCD(int64_t lhs, int64_t rhs) {
    while (true) {
        if (lhs == 0)
            return rhs;
        rhs %= lhs;
        if (rhs == 0)
            return lhs;
        lhs %= rhs;
    }
    return 0;
}

int64_t LCM(int64_t lhs, int64_t rhs) {
    int64_t tmp = GCD(lhs, rhs);
    return tmp ? (lhs / tmp * rhs) : 0;
}

int main() {

    std::string line;
    std::unordered_map<Module, std::vector<std::string>> modules;

    while (std::getline(std::cin, line)) {
        int pos = line.find("->");
        std::string left = line.substr(0, pos - 1);
        Module m;
        m.name = left.substr(1);
        switch (left[0]) {
        case '%':
            m.type = FLIPFLOP;
            break;
        case '&':
            m.type = CONJUNCTION;
            break;
        default:
            m.type = SENDER;
            m.name = left;
            break;
        }
        std::string right = line.substr(pos + 3);
        int i = 0;
        std::string tmp = "";
        while (i < right.length()) {
            if (right[i] == ',') {
                modules[m].push_back(tmp);
                tmp = "";
            } else if (right[i] != ' ') {
                tmp += right[i];
            }
            i++;
        }
        modules[m].push_back(tmp);
    }

    for (auto &[k, v] : modules) {
        for (auto &s : v) {
            auto it = modules.find({s, NONE, SENDER});
            if (it != modules.end() && it->first.type == CONJUNCTION) {
                auto node = modules.extract(it);
                node.key().last[k.name] = LOW;
                modules.insert(std::move(node));
            }
        }
    }

    Module button = {"button", LOW, SENDER};
    modules[button] = {"broadcaster"};
    std::unordered_map<std::string, int> cycle = {
        {"nd", 0}, {"vd", 0}, {"pc", 0}, {"tx", 0}};
    int64_t res = 0;
    std::queue<Module> q;
    while (true) {
        q.push(button);
        res++;
        while (!q.empty()) {
            Module cur = q.front();
            q.pop();

            for (auto &n : modules[cur]) {

                if (modules.find({n, NONE, SENDER}) == modules.end()) {
                    continue;
                }

                auto node = modules.extract({n, NONE, SENDER});
                switch (node.key().type) {
                case FLIPFLOP:
                    if (cur.signal == LOW) {
                        node.key().on = !node.key().on;
                    } else {
                        break;
                    }

                    if (node.key().on) {
                        node.key().signal = HIGH;
                        q.push(node.key());
                    } else {
                        node.key().signal = LOW;

                        q.push(node.key());
                    }
                    break;
                case CONJUNCTION:
                    node.key().last[cur.name] = cur.signal;
                    node.key().signal = LOW;
                    for (auto &p : node.key().last) {
                        if (p.second == LOW) {
                            node.key().signal = HIGH;
                            break;
                        }
                    }

                    q.push(node.key());
                    break;

                case SENDER:
                    node.key().signal = cur.signal;
                    q.push(node.key());
                    break;
                }

                modules.insert(std::move(node));
            }

            if (modules.find({"nd", NONE, SENDER})->first.signal == HIGH) {
                if (cycle["nd"] == 0) {
                    cycle["nd"] = res;
                    std::cout << cycle["nd"] << std::endl;
                }
            }

            if (modules.find({"vd", NONE, SENDER})->first.signal == HIGH) {
                if (cycle["vd"] == 0) {
                    cycle["vd"] = res;
                    std::cout << cycle["vd"] << std::endl;
                }
            }

            if (modules.find({"pc", NONE, SENDER})->first.signal == HIGH) {
                if (cycle["pc"] == 0) {
                    cycle["pc"] = res;
                    std::cout << cycle["pc"] << std::endl;
                }
            }

            if (modules.find({"tx", NONE, SENDER})->first.signal == HIGH) {
                if (cycle["tx"] == 0) {
                    cycle["tx"] = res;
                    std::cout << cycle["tx"] << std::endl;
                }
            }

            if (cycle["nd"] != 0 && cycle["vd"] != 0 && cycle["pc"] != 0 &&
                cycle["tx"] != 0) {
                std::cout << LCM(cycle["nd"],
                                 LCM(cycle["vd"],
                                     LCM(cycle["pc"], cycle["tx"])))
                          << std::endl;
                return 0;
            }
        }
    }

    std::cout << res << std::endl;

    return 0;
}
