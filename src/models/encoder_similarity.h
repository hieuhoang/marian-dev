#pragma once

#include "marian.h"

#include "model_base.h"
#include "encoder.h"

namespace marian {

class EncoderSimilarityBase : public models::ModelBase {
public:
  virtual void load(Ptr<ExpressionGraph> graph,
                    const std::string& name,
                    bool markedReloaded = true) = 0;

  virtual void save(Ptr<ExpressionGraph> graph,
                    const std::string& name,
                    bool saveTranslatorConfig = false) = 0;

  virtual void clear(Ptr<ExpressionGraph> graph) = 0;

  virtual Expr build(Ptr<ExpressionGraph> graph,
                     Ptr<data::Batch> batch,
                     bool clearGraph = true) = 0;

  virtual Expr build(Ptr<ExpressionGraph> graph,
                     Ptr<data::CorpusBatch> batch,
                     bool clearGraph = true) = 0;

  virtual Ptr<Options> getOptions() = 0;
};

class EncoderSimilarity : public EncoderSimilarityBase {
protected:
  Ptr<Options> options_;

  std::string prefix_;

  std::vector<Ptr<EncoderBase>> encoders_;

  bool inference_{false};

  std::set<std::string> modelFeatures_;

  Config::YamlNode getModelParameters();

public:
  typedef data::Corpus dataset_type;

  EncoderSimilarity(Ptr<Options> options);

  virtual Ptr<Options> getOptions() { return options_; }

  std::vector<Ptr<EncoderBase>>& getEncoders();

  void push_back(Ptr<EncoderBase> encoder);

  virtual void load(Ptr<ExpressionGraph> graph,
                    const std::string& name,
                    bool markedReloaded = true);

  virtual void save(Ptr<ExpressionGraph> graph,
                    const std::string& name,
                    bool saveTranslatorConfig = false) {}

  virtual void clear(Ptr<ExpressionGraph> graph);

  template <typename T>
  T opt(const std::string& key) {
    return options_->get<T>(key);
  }

  template <typename T>
  void set(std::string key, T value) {
    options_->set(key, value);
  }

  /*********************************************************************/

  virtual Expr build(Ptr<ExpressionGraph> graph,
                     Ptr<data::CorpusBatch> batch,
                     bool clearGraph = true);

  virtual Expr build(Ptr<ExpressionGraph> graph,
                     Ptr<data::Batch> batch,
                     bool clearGraph = true);

};


}